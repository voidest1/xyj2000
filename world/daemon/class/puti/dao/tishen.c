#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	//string msg,start;
	//int ap, dp, success;
	//target = offensive_target(me);
	//always use the one who is fighting me as target.
	int t;
    t=me->query("no_dead_time");

	if( me->is_busy())
		return notify_fail("你正忙着呢，先应付眼前的事吧。\n");

	if( (int)me->query("mana") < 300 )
		return notify_fail("你的法力不够了！\n");

	if( (int)me->query("sen") < (int)me->query("max_sen")/5 )
		return notify_fail("你精神太差，难以集中精力念咒。\n");

	if( (int)me->query_skill("dao", 1) < 200)
		return notify_fail("你未曾学会替身。\n");

    if(me->query_temp("no_dead"))
           return notify_fail("你眼下有替身。\n");

	if(t<time()&&time()<t+1800)
		return notify_fail("你用替身的时辰还未到。\n");

	

     
	message_vision(HIC"$N喃喃的念了几句咒语,化了几道符！\n"NOR,me);
	me->add("mana", -300);
	
	if(time()>t+1800)
	{
	me->set("no_dead_time",time());
	me->set_temp("no_dead",1);
	message_vision(HIC"$N好像符咒起作用了！\n"NOR,me);
	call_out("remove_no_dead",1800,me);
	}
	return 5;
	
}



void remove_no_dead(object me) 
{ if (!me) return;
  if (!me->query_temp("no_dead")) return;
  if (me) me->delete_temp("no_dead");
message_vision(HIC"$N感觉符咒隐隐的消散了！\n"NOR,me);
return;

}