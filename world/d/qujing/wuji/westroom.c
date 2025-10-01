// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/mimi/zhuziguo/westroom  snowcat moved to /d/qujing/wuji

inherit ROOM;

void create ()
{
  set ("short", "西厢房");
  set ("long", @LONG

此间乃寺中主持的禅房，但因近来夜间闹鬼，主持已搬去别处。屋
中陈设甚是典雅。两边书架上摆满了经书，朝南的案上有一鼎香炉
却好象好久没人上香了。

LONG);

  set("light_up", 1);
  set("exits", ([ /* sizeof() == 1 */
    "east" : __DIR__"zheng",
  ]));
  set("sleep_room",1);

  setup();
}

void init()
{
  add_action ("do_sleep","sleep");
}

int do_sleep (string arg)
{
  object who = this_player();
  int phase = NATURE_D->query_current_day_phase();

  if (random(5))
    return 0;
  if (present("ghost guo wang"))
    return 0;
  if (who->query("combat_exp")<50000)
    return 0;
  if (phase > 0 && phase < 5)
    return 0;

  message_vision ("$N试着躺下想睡着，但心里有点忐忑不安。\n",who);
  remove_call_out ("create_king");
  call_out ("create_king",2+random(10));
  return 1; 
}

int create_king() 
{
  object  king;

  if(!present("ghost guo wang"))
  {
    king = new("/d/qujing/wuji/npc/king.c");
    king->move("/d/qujing/wuji/westroom.c");
  }

  return 1;
}

void set_given()
{
  object me = this_object();

  me->set("has_given",1);
  remove_call_out("reset_given");
  call_out("reset_given",900);
}

void reset_given ()
{
  object me = this_object();

  me->set("has_given",0);
}
