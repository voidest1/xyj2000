// cracked by vikee 2/09/2002   vikee@263.net
// Room: /moon/road.c

inherit ROOM;

void create ()
{
  set ("short", "回廊");
  set ("long", @LONG

曲折游廊，阶下石子漫成甬路，有千百翠竹遮映．
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"ghg_zhengdian.c",
  "north" : __DIR__"huilang1.c",
  "west" : __DIR__"change_room.c",
]));

  setup();
}