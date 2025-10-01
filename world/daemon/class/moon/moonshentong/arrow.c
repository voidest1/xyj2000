// cracked by vikee 2/09/2002   vikee@263.net
// arrow.c
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	int success_adj, damage_adj;

	success_adj = 100;
	damage_adj = 100;

	if( !target ) target = offensive_target(me);

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("你要对谁施展落日神箭？\n");

	if((int)me->query("mana") < 25+2*(int)me->query("mana_factor") )
		return notify_fail("你的法力不够！\n");

	if((int)me->query("sen") < 50 )
		return notify_fail("你无法集中精力瞄准！\n");

	me->add("mana", -25-2*(int)me->query("mana_factor"));
		me->receive_damage("sen", 10);

	if( random(me->query("max_mana")) < 50 ) {
		write("后羿正跟老婆赌气，来不了了！\n");
		return 1;
	}

  if (!wizardp(me))
	SPELL_D->attacking_cast(
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
		HIC "$N口中念了几句咒文，随着一声“后羿在此！”半空中现出一位身披虎皮的大汉。\n只见他张弓搭箭，“嗖”的一声，一只蓝汪汪的长箭向$n激射而下！\n" NOR,
			//initial message
		HIC "结果长箭从$n身上透体而过，顿时血花飞溅！\n" NOR, 
			//success message
		HIC "只见$n轻轻一跳，长箭正好插在$n脚边，兀自颤动不休！\n" NOR, 
			//fail message
        HIC "但是$n以法力一拨，长箭“嗖”的一声折向$N！\n" NOR,
			//backfire initial message
		HIC "结果长箭从$n身上透体而过，顿时血花飞溅！\n" NOR
			//backfire hit message. note here $N and $n!!!
	);

else
{
  damage_adj=me->query_skill("moonshentong",1);
  SPELL_D->attacking_cast(me,target,success_adj,damage_adj,"both",
  HIC "$N口中念了几句咒文，随着一声“后羿在此！”半空中现出一位身披虎皮的大汉。\n只见他从$N手中接过落日神箭，张弓搭箭，“嗖”的一声，一只蓝汪汪的长箭向$n激射而下！\n" NOR,
        HIC "结果落日神箭从$n身上透体而过，顿时血花飞溅！\n" NOR, 
        HIC "只见$n轻轻一跳，落日神箭正好插在$n脚边，兀自颤动不休！\n" NOR, 
        HIC "但是$n以法力一拨，落日神箭“嗖”的一声折向$N！\n" NOR,
        HIC "结果落日神箭从$n身上透体而过，顿时血花飞溅！\n" NOR
 );
}
	me->start_busy(1+random(2));
	return 3+random(5);
}

