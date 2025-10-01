//翻江倒海倾吴蜀 by hexiu

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

int exert(object me, object target)
{
       object where;
        int i, skill, damage, force;
    

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("你要倒谁？\n");

	if ( me->query_temp("fjdh_busy") == 1)
        return notify_fail("歇会再翻！\n");

	where=environment(me);
	if( where->query("no_fight") )
		return notify_fail("安全区内不能乱叫！\n");

        if( !me->is_fighting() )
                return notify_fail("翻江倒海只能在战斗中使用。\n");
	
		if( me->query_skill("dragonforce",1) < 200 )
                return notify_fail("你的功力还不够翻江倒海。\n");


        if( (int)me->query("force") < 200 )
                return notify_fail("你的内力不够。\n");
	if( (int)me->query("kee") < 100)
		return notify_fail("你的力气不够了。\n");


        skill = me->query_skill("force");
	force = me->query("max_force");
        me->add("force", -150);
        me->receive_damage("kee", 50);

       // me->start_busy(5);
		me->set_temp("fjdh_busy",1);
        me->set_temp("no_move",1);
		call_out("remove_no_move",3,me);
        call_out("remove_effect",6+random(3),me);
	message_vision(HIR "\n$N退后两步，深深地吸一口气，猛然发出翻江倒海的咆哮！\n\n"
NOR, me);
      

	if( skill/2 + random(skill/2) > (int)target->query("cps") * 2 ) 
	{

                damage = skill + force/10 - ((int)target->query("max_force") / 10);
                if( damage > 0 ) 
				{
                        target->receive_damage("sen", damage/2, me);
                        if( (int)target->query("force") < skill * 2 )
                                target->receive_wound("sen", damage/10, me);
						if (target->query_temp("no_dodge") == 1) 
    //                    message_vision(HIY"\n$N还在地上趴着呢！\n"NOR,target);
write("对方眼下还在趴着！\n");
						else{
                              target->set_temp("no_dodge",1);
							  message_vision(HIW"\n一股罡气袭来，直接将$N击倒在地！\n"NOR,target);
                     //   tell_object(target, "你觉得一股罡气袭来，直接将你冲倒在地！\n");
             call_out("no_dodge_end", me->query_skill("dragonforce",1)/20+random(3), target);
							}
				}
				else tell_object(me,HIW "\n好像力道不够！\n"NOR);
	}
	else 
		tell_object(me,HIW "\n糟糕！力道不够！\n"NOR);

		COMBAT_D->report_sen_status(target);		
        if( living(target) ) target->kill_ob(me);

        

        return 1;
}


void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("fjdh_busy");
}

void remove_no_move(object me) {
  if (me) me->delete_temp("no_move");
}
void no_dodge_end(object target)
{
	if (!target) return;
	target->delete_temp("no_dodge");
	message_vision(HIY"\n$N拍拍身的土，爬了起来！\n"NOR,target);
	return;
}
