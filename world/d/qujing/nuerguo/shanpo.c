// cracked by vikee 2/09/2002   vikee@263.net
// created by snowcat.c 4/4/1997
// room: /d/nuerguo/shanpo.c

inherit ROOM;

void create ()
{
  set ("short", "山坡");
  set ("long", @LONG

你爬行在一面斜斜的山坡上，西边的坡上影影约约像是有一
座亭子。再朝自己的脚下看一看，远远的是一片绿树丛。

LONG);

  set("exits", ([
        "westup"   : __DIR__"changbie",
      ]));
  set("outdoors", __DIR__"");

  setup();
}






