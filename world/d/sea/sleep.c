// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/rainy/sea/sleep.c
inherit ROOM;
inherit "/d/wiz/no_get";

void create ()
{
  set ("short", "睡房");
  set ("long", @LONG

这里是龙宫中的睡房。

LONG);

  set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"mulang2.c",
]));
  set("no_magic",1);
        set("sleep_room",1);
        set("if_bed",1);

//      
        set("water", 1);
//  
  setup();
}
