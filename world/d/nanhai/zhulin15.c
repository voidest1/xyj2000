// cracked by vikee 2/09/2002   vikee@263.net
// Room: /d/nanhai/zhulin.c

inherit ROOM;

void create()
{
	set("short", "紫竹林");
	set("long", @LONG

普陀后山的紫竹林。也是观音菩萨闲憩常到的所在。紫竹细疏，
清风微拂。漫步于此，世事之纷扰顿时烟消云散。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"pool",
  "west" : __DIR__"zhulin16",
  "south" : __DIR__"zhulin"+sprintf("%d", 6+random(9)),
  "east" : __DIR__"zhulin17",
]));
  set("objects", ([ /* sizeof() == 2 */
  "/d/nanhai/obj/jingu1" : 1,
]));



	setup();
	replace_program(ROOM);
}
