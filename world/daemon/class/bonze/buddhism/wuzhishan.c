// cracked by vikee 2/09/2002   vikee@263.net
// bighammer.c
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	int success_adj, damage_adj ,suc,howlong;

	success_adj = 250;
	damage_adj = 200;

	if(me->query("family/family_name") != "南海普陀山")
                return notify_fail("不入佛门请不来五指山！\n");

	if(me->query_skill("buddhism",1)<200) 
		return notify_fail("你的修为不够深，还请不来五指山。\n");

     //   if(!me->query("wuzhishan")) 
         //       return notify_fail("你师父还没教会你怎么请来五指山。\n");

	if( !target ) target = offensive_target(me);

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("你要用五指山压谁？\n");

	if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 200 )
		return notify_fail("你无法集中精力，就别请五指山了！\n");


	me->add("mana", -25-2*(int)me->query("mana_factor"));
	me->receive_damage("sen", 100);

	if( random(me->query("max_mana")) < 50 ) {
		write("好象没反应，再请一次吧！\n");
		return 1;
	}
    suc = 0;
	suc = SPELL_D->attacking_cast(
		me, 
			//attacker 
		target, 
			//target
		success_adj, 	
			//success adjustment
		damage_adj, 	
			//damage adjustment
		"both", 		
			//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "$N口中念了几句咒文，半空中现出一座五指山！\n呼！地一声向$n当头压了下来！\n" NOR,
			//initial message
		HIC "结果砸个正着，直接把$n压在地上！\n" NOR, 
			//success message
		HIC "但是$n在千钧一发之际躲了开来。\n" NOR, 
			//fail message
		HIC "但是五指山被$n以法力一引，反而向$N的顶门压了下来！\n" NOR, 
			//backfire initial message
		HIC "结果砸个正着，直接把$n压在地上！\n" NOR
			//backfire hit message. note here $N and $n!!!
	);
	if (suc > 0) 
	{
		if(target->query_temp("silence")) 
		{write("对方正在沉默中！\n");}
    	else
		{target->set_temp("silence",1);
    	message_vision(HIR"\n$n觉得胸中沉闷，一句话都说不出来！\n"NOR,me,target);
howlong = (int)(me->query_skill("buddhism",1)/20)+random(3);
    	call_out("remove_silence",howlong,target);
		}
	
	}
   // if( wizardp(me) ) write(HIY"判定："+suc+"\n"NOR);
	me->start_busy(1);
	return 3+random(5);
}



void remove_silence(object target)
{
  if (!target || !living(target) ) return;
  target->delete_temp("silence");
  message_vision(HIR"\n$N觉得缓过劲来了！\n"NOR,target);
return;
}
