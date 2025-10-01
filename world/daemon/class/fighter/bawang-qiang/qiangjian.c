// add by hexiu
// 枪里加锏

#include <ansi.h>
#include <weapon.h>

inherit SSERVER;

int perform(object me, object target)
{
	int skill, skill1, skill2;
	object weapon1, weapon2,sweapon,ob;

	if(!target) target = offensive_target(me);

	if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这一招「枪里加锏」？\n");

	if(!me->is_fighting())
                return notify_fail("「枪里加锏」只能在战斗中使用！\n");

	if((int)me->query("max_force") < 500)
		return notify_fail("你的内力不够！\n");

        if((int)me->query("force") < 500 )
                return notify_fail("你的内力不足！\n");

	if((int)me->query("sen") < 250)
		return notify_fail("你的精神不足，没法子施用外功！\n");

	if((int)me->query_skill("bawang-qiang",1) < 100)
		return notify_fail("你的霸王枪级别还不够，使用这一招会有困难!\n");

	if((int)me->query_skill("wusi-mace",1) < 100)
		return notify_fail("你的无私锏级别还不够，使用这一招会有困难!\n");
     
	if(me->query_temp("QJ_perform"))
        return notify_fail("绝招不能用太多!\n");

    ob=target->query_temp("weapon");
	weapon1=me->query_temp("weapon");
    if(me->query_temp("secondary_weapon")) sweapon=me->query_temp("secondary_weapon");
	weapon2=present("mace", me);
	
	if(!objectp(weapon2)) 
		return notify_fail("没锏怎么枪里加锏?\n");

	message_vision(HIC"\n$N运足精神，抖手刺出一枪!\n"NOR, me, target);
	
    me->set_temp("BWQ_perform", 7);
	COMBAT_D->do_attack(me, target, weapon1);
    me->delete_temp("BWQ_perform");
	
    if((int)me->query_skill("bawang-qiang",1) > 200 && me->query("family/family_name") == "将军府" )
	{  
		if(target->query_temp("no_parry")==0 && ob !=0)
		{message_vision(HIC"\n$N一反手，甩枪荡开了$n手中的"+ob->query("name")+"!\n"NOR, me, target);
	target->set_temp("no_parry",1);
	call_out("remove_no_parry",me->query_skill("bawang-qiang",1)/20+random(3),target);}
		else {write("对方眼下不能招架！\n");}
	
	}

        message_vision(HIC"\n趁着$n手忙脚乱，$N抽出"+weapon2->query("name")+HIC"击出两下"NOR, me, target);

	weapon1->unequip();
	if(sweapon) sweapon->unequip();
	weapon2->wield();

	me->set_temp("WSJ_perform", 4);
	COMBAT_D->do_attack(me, target, weapon2);

	me->set_temp("WSJ_perform", 5);
	COMBAT_D->do_attack(me, target, weapon2);

	if((int)me->query_skill("wusi-mace",1) > 200)
	{me->set_temp("WSJ_perform", 7);
	COMBAT_D->do_attack(me, target, weapon2);}

	me->delete_temp("WSJ_perform");

	me->receive_damage("sen", 100);
	me->add("force", -100);

	if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }

	weapon2->unequip();
	weapon1->wield();
	//if(sweapon) sweapon->wield();

       me->set_temp("QJ_perform",1);
        me->set_temp("no_move",1);
		call_out("remove_no_move",3,me);
        call_out("remove_effect",3+random(3),me);

        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("QJ_perform");
}

void remove_no_move(object me) {
  if (me) me->delete_temp("no_move");
}

void remove_no_parry(object target)
{
	if (!target) return;
	target->delete_temp("no_parry");
	message_vision(HIY"\n$N活动了一下发麻的手腕！\n"NOR,target);
	return;
}
