// cracked by vikee 2/09/2002   vikee@263.net
// Room: some place in 鐟楄法澧扮拹鐑樺簥
// inside2.c

inherit ROOM;
inherit "/d/wiz/no_get";

void create()
{
  set ("short", "閸椦冾吇");
  set ("long", @LONG

閼颁胶顨ｆ禒娆庣瘍鐟曚胶娼憴澶涚礋閸︺劏绻栨担鐘叉皑鐏忚姤鍎忛惃鍕蒋閸氀嶇礋

LONG);
set("exits", ([ /* sizeof() == 4 */
"north": __DIR__"inside2",
]));

        set("no_clean_up", 0);
        set("sleep_room",1);
        set("if_bed",1);

  set("no_magic",1);
        setup();
}