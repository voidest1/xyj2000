#!/usr/bin/env zsh
# macOS-safe zsh script: convert legacy Chinese encodings to UTF-8 (recursively)
# - Tries GB18030, GBK, CP936, GB2312
# - Fixes mojibake (UTF-8 mis-saved from GBK/18030 via ISO-8859-1 roundtrip)
# - Skips binary files
# Options:
#   -r <root>  : root directory (default: .)
#   -n         : dry-run (show what would change, do not modify files)
#   -b         : backup original files as <file>.bak before overwriting
#   -v         : verbose
# Usage:
#   ./convert-to-utf8.zsh -r . -b -v
#   ./convert-to-utf8.zsh -n   # just see what would be converted

emulate -L zsh -o err_exit -o pipefail
set -u

# ---------- options ----------
typeset -g ROOT="."
typeset -g DRYRUN=0
typeset -g BACKUP=0
typeset -g VERBOSE=0

while getopts "r:nbv" opt; do
  case "$opt" in
    r) ROOT="$OPTARG" ;;
    n) DRYRUN=1 ;;
    b) BACKUP=1 ;;
    v) VERBOSE=1 ;;
  esac
done
shift $((OPTIND-1))

# ---------- helpers ----------
log() { print -r -- "$@" }
vlog() { (( VERBOSE )) && log "$@"; }

# is file likely text? (avoid binary)
is_text() {
  local f="$1"
  local mime
  mime=$(file -I "$f" 2>/dev/null | awk -F': ' '{print $2}')
  [[ "$mime" != *"charset=binary"* ]]
}

# is valid UTF-8 and contains no U+FFFD (�)
is_valid_utf8_file() {
  local f="$1"
  iconv -f UTF-8 -t UTF-8 "$f" -o /dev/null 2>/dev/null || return 1
  LC_ALL=C grep -q $'\xEF\xBF\xBD' "$f" && return 1
  return 0
}

# heuristic: looks like UTF-8 mojibake (e.g., "Ã ", "Â·", etc.)
looks_like_mojibake() {
  local f="$1"
  # Common patterns when GBK was mis-decoded as UTF-8, tweak as needed
  LC_ALL=en_US.UTF-8 grep -Eq 'Ã.|Â.|��' "$f"
}

# run iconv and validate result (no U+FFFD). If ok, move into place.
try_convert() {
  local from="$1" f="$2" tmp="$3"
  if iconv -f "$from" -t UTF-8 "$f" > "$tmp" 2>/dev/null; then
    if ! LC_ALL=C grep -q $'\xEF\xBF\xBD' "$tmp"; then
      if (( DRYRUN )); then
        log "Would convert: $f  ($from -> UTF-8)"
        rm -f -- "$tmp"
      else
        (( BACKUP )) && cp -p -- "$f" "$f.bak"
        mv -f -- "$tmp" "$f"
        # normalize line endings if dos2unix exists
        command -v dos2unix >/dev/null && dos2unix -q "$f" 2>/dev/null || true
        log "Converted: $f  ($from -> UTF-8)"
      fi
      return 0
    fi
  fi
  return 1
}

# fix mojibake: UTF-8 text that actually contains GBK bytes mis-saved
try_fix_mojibake() {
  local from="$1" f="$2" tmp="$3"
  if iconv -f UTF-8 -t ISO-8859-1 "$f" 2>/dev/null \
     | iconv -f "$from" -t UTF-8 > "$tmp" 2>/dev/null; then
    if ! LC_ALL=C grep -q $'\xEF\xBF\xBD' "$tmp"; then
      if (( DRYRUN )); then
        log "Would fix mojibake: $f  (utf8→latin1→$from -> UTF-8)"
        rm -f -- "$tmp"
      else
        (( BACKUP )) && cp -p -- "$f" "$f.bak"
        mv -f -- "$tmp" "$f"
        command -v dos2unix >/dev/null && dos2unix -q "$f" 2>/dev/null || true
        log "Fixed mojibake: $f  (utf8→latin1→$from -> UTF-8)"
      fi
      return 0
    fi
  fi
  return 1
}

# ---------- main ----------
# Use BSD find (-E supports extended regex). We do NOT filter by extensions.
# -print0 to be safe with weird filenames.
vlog "Root: $ROOT"
vlog "Dry-run: $DRYRUN  Backup: $BACKUP  Verbose: $VERBOSE"

# We’ll keep a conversion log
LOGFILE="convert-to-utf8-$(date +%Y%m%d-%H%M%S).log"
exec > >(tee -a "$LOGFILE") 2>&1

find -E "$ROOT" -type f -print0 | while IFS= read -r -d '' f; do
  # quick stat
  [[ -r "$f" && -s "$f" ]] || continue

  # skip obvious binary files (packed objs in .git will be detected as binary)
  if ! is_text "$f"; then
    vlog "Skip (binary): $f"
    continue
  fi

  # If already valid UTF-8 and not mojibake-patterned, skip
  if is_valid_utf8_file "$f" && ! looks_like_mojibake "$f"; then
    vlog "OK (UTF-8): $f"
    continue
  fi

  # temp file
  tmp="$(mktemp "/tmp/iconv.$$.XXXXXX")" || { log "mktemp failed"; exit 1; }
  trap 'rm -f -- "$tmp" 2>/dev/null || true' INT TERM EXIT

  # 1) GB18030 first
  if try_convert "GB18030" "$f" "$tmp"; then continue; fi
  # 2) GBK / CP936
  if try_convert "GBK" "$f" "$tmp"; then continue; fi
  if try_convert "CP936" "$f" "$tmp"; then continue; fi
  # 3) GB2312 (older files)
  if try_convert "GB2312" "$f" "$tmp"; then continue; fi

  # 4) Mojibake repair attempts
