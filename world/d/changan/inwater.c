// cracked by vikee 2/09/2002   vikee@263.net
inherit ROOM;

void create ()
{
  set ("short", "娉炬按");
  set ("long", @LONG

鍛ㄥ洿鏄綈鑵版繁鐨勬渤姘达紝浠庡洓鍛ㄧ殑鏅壊鏉ョ湅澶ф鏄湪闀垮畨鍩庡崡锛屾尘
姘翠箣涓紟娴佹按娓呮緢瑙佸簳锛岃繙澶勮繕鏈夊嚑鏉″皬鑸癸紟
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"eside1",
]));
  set("objects", ([ /* sizeof() == 2 */
  "/d/sea/npc/long7.c" : 1,
]));

  setup();
}