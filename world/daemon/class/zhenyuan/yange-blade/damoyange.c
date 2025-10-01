#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
object weapon;
 string msg;
if( !target ) target = offensive_target(me);
if( !target
||      !target->is_character()
||      target->is_corpse()
||      target==me)
return notify_fail("你要对谁施展这一招「大漠雁歌」？\n");
if(!me->is_fighting())
return notify_fail("「大漠雁歌」只能在战斗中使用！\n");
if((int)me->query("max_force") < 500 )
return notify_fail("你的内力不够！\n");
if((int)me->query("force") < 500 )
return notify_fail("你的内力不足！\n");
if((int)me->query("sen") < 500 )
return notify_fail("你的精神不足，没法子施用外功！\n");
if((int)me->query_skill("yange-blade", 1) < 80)
return notify_fail("你的雁歌刀法级别还不够，使用这一招会有困难！\n");
if (me->query_skill_mapped("force")!="zhenyuan-force")
return notify_fail("大漠雁歌必须配合镇元神功才能使用。\n");

me->delete("env/brief_message");
target->delete("env/brief_message");

message_vision(HIR"\n$N大喝一声,只见飞沙走石,大雁南行,「大漠雁歌」一招一气呵成!!!\n"NOR,me,target);

// message_vision( HIY  "孤城落日！\n" NOR,me,target);
me->set_temp("yange_perform", 1);
COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
// message_vision( HIC  "大漠穷秋！\n" NOR,me,target);
me->set_temp("yange_perform", 2);
COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
// message_vision( HIG  "边风飘摇！\n" NOR,me,target);
me->set_temp("yange_perform", 4);
COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
// message_vision( HIW  "塞雁南飞！\n" NOR,me,target);
me->set_temp("yange_perform", 6);
COMBAT_D->do_attack(me, target, me->query_temp("weapon"));       
me->delete_temp("yange_perform");      
me->receive_damage("sen", 100);   
me->add("force", -100);

if( !target->is_fighting(me) ) {
if( living(target) ) {
if( userp(target) ) target->fight_ob(me);
else target->kill_ob(me);
}
}
me->start_busy(2+random(1));
return 1;
}
