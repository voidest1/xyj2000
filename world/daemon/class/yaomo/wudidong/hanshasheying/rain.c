//
//rain.c by hexiu

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「暴风骤雨」？\n");

     

        if((int)me->query("max_force") < 500 )
                return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("你的精神不足，没法子施用外功！\n");

        if((int)me->query_skill("hanshasheying", 1) < 100)
                return notify_fail("你的含沙射影级别还不够，使用这一招会有困难！\n");
              
        if (me->query_skill_mapped("force")!="huntian-qigong")
                return notify_fail("暴风骤雨必须配合浑天气功才能使用。\n");

        if (me->query_temp("rain_busy"))
                return notify_fail("绝招滥使就不灵了！\n");
              
        //me->delete("env/brief_message");
        //target->delete("env/brief_message");

        message_vision(MAG"\n暗处隐隐显出$N的身影，只见$N一扬手!\n"NOR,me,target);
		message_vision(HIC"\n数枚"+weapon->query("name")+"暴风骤雨般的向$n飞来!\n"NOR,me,target);

        
        
        
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                         target->kill_ob(me);
                }
        }

        me->set_temp("HSSY_perform", 4);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("HSSY_perform", 1);  
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

        
        me->set_temp("HSSY_perform", 6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        
        if((int)me->query_skill("hanshasheying",1) > 200)
		{
			me->set_temp("HSSY_perform", 5);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));  
		}

        me->delete_temp("HSSY_perform");

        me->receive_damage("sen", 100);
        me->add("force", -100);
        

       /* 
	   if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
		*/

        me->set_temp("rain_busy",1);
		call_out("remove_rain_busy",9+random(3),me);
        //me->start_busy(2+random(1));

        return 1;
}

void remove_rain_busy(object me)
{ 
        if (!me) return;
		if (me->query_temp("rain_busy"))
        me->delete_temp("rain_busy");
}         