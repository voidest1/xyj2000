// cracked by vikee 2/09/2002   vikee@263.net
// Room: /moon/road.c

inherit ROOM;

void create ()
{
  set ("short", "鍥炲粖");
  set ("long", @LONG

鏇叉姌娓稿粖锛岄樁涓嬬煶瀛愭极鎴愮敩璺紝鏈夊崈鐧剧繝绔归伄鏄狅紟
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"ghg_zhengdian.c",
  "north" : __DIR__"huilang1.c",
  "west" : __DIR__"change_room.c",
]));

  setup();
}






