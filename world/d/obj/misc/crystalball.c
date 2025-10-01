// cracked by vikee 2/09/2002   vikee@263.net

#define RUMORCENTER "/d/city/rumorcenter"
#include <ansi.h>

inherit ITEM;
object room;

void create() {

  set_name("水晶球", ({"shuijing qiu","crystal","ball","qiu"}));
  set_weight(200);
  set("unit", "只");
  set("long", "一只鎏光四溢的水晶球，虽然不能未卜先知，后见之明(detect)倒也马马虎虎。\n");
  set("value", 1000);
  setup();
//  room=find_object(RUMORCENTER);
  room=load_object(RUMORCENTER);
  set("room",room);
}

void init() {
  add_action("do_detect","detect");
}

int do_detect(string arg) {
  mapping rumor;
  int number;
  object me=this_player();
  object ob=this_object();

  if (! arg || sscanf(arg, "%d", number)!=1) 
    return notify_fail("用法： ｄｅｔｅｃｔ （１－１０） \n");
  if (number<1 || number>10) return notify_fail("用法错误！\n");
  
  if (!room) {
    set("value",0);
    write("这只水晶球已经失去神力了。\n");    
    write("水晶球化成一滩清水流了一地。\n");
    destruct(this_object());
    return 1;
  }

  if (me->query("mana")<100) return notify_fail("你的法力不够，无法与水晶球沟通。\n");

  rumor=room->reveal(number);
  set("rumor",rumor);

  me->add("mana",-10);
  message_vision(HIG"$N捧着水晶球，口中喃喃自语。\n"NOR,me);
  if (!rumor) {
    tell_object(me,"可是什么也没有发生。\n");
    return 1;
  }
  tell_object(me,CYN"你请教水晶球：刚才「"+rumor["body"]+"」是谁说的？\n"NOR);
  if (!rumor["disclose"])
     tell_object(me,HIB"水晶球回答你：天机不可泄露。\n"NOR);
  else {
    tell_object(me,MAG"水晶球缓缓的转动着，你仿佛从中看到了一个身影。\n"); 
    tell_object(me,HIR"人影越来越清晰，你仔细一看，原来是"HIW
               +rumor["name"]+HIR"("+rumor["id"]+")！\n"NOR);
  }

  return 1;
}  
