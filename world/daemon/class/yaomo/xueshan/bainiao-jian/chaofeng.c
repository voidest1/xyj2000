// cracked by vikee 2/09/2002   vikee@263.net
// 百鸟朝凤
/*
requirement: sword+bainiao_jian+throwing >80 藏了暗器的剑中可发暗器
                                         >150 剑气伤人
damage : 发出暗器/剑气   1. random 发出5-10股
         命中几率      (me->a)/(target->d)*0.3
         伤害:         银针: 20+me->query_temp("apply/damage") 
	               毒针: <崭缺>	
                       孔雀翎: 50+me->query_temp("apply/damage") 
                       剑气: me->query("force_factor")
		       剑气+暗器 : 伤害累加
*/

#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;

        string msg;
        int ii,req,num_anqi,num_hit,max_hit,hitt,damage,op,opfa,remain;
        string anqi_type,b_unit;

   int wound=0;

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
           return notify_fail("你要攻击谁？\n");
        
      weapon = me->query_temp("weapon");
      req=(int)me->query_skill("sword", 1)+(int)me->query_skill("bainiao-jian", 1)+(int)me->query_skill("throwing", 1); 


      if (weapon)  
        {
        if (weapon->query("anqi/allow") != 1) num_anqi=0;
        else num_anqi=weapon->query("anqi/now");
        }

      if (me->query_skill_mapped("force")!="ningxie-force")
                return notify_fail("百鸟朝凤必须配合冰谷凝血功才能使用。\n");
      if(req < 80)
            return notify_fail("你剑中打暗器的功夫还不到火候！\n");
      if(req < 150 && weapon->query("anqi/now") ==0)
            return notify_fail("你剑中没有暗器可打！\n");
       if (me->query("force")<200)
           return notify_fail("你内力不继，难以御剑飞针。\n");

  if (me->query_temp("chaofeng_busy")) return notify_fail("出奇才能制胜，百鸟朝凤多使就不灵了。\n");
        me->add("force", -100);

        if(num_anqi <=0) 
           { anqi_type="剑气"; damage=me->query("force_factor")+10; }
        else if (req < 150)
           { anqi_type=weapon->query("anqi/type"); damage=me->query_temp("apply/damage");}
        else 
           { anqi_type=weapon->query("anqi/type")+"加着剑气";
             damage=me->query_temp("apply/damage")+me->query("force_factor")+10;}
         
        msg = HIW"只见$N手中"+weapon->query("name")+HIW"急颤，幻出满天剑芒，无数"
                 +anqi_type+HIW"有如百鸟投林般向$n扑来！\n" NOR;

        if (num_anqi > 10 || num_anqi == 0) max_hit=10;
        else max_hit=weapon->query("anqi/now");

        num_hit=random(max_hit/2)+(max_hit/2);

        if (!target->is_fighting(me)) opfa=30;
        else opfa=15;

        if (target->query("combat_exp")  !=0 ) 
               op= me->query("combat_exp")*opfa/target->query("combat_exp");
        else op=10;
        hitt=0;	
        for (ii=1;ii<=num_hit;ii++)  
          {if (op > random(100)) hitt++;}


        if (weapon->query("anqi/type")=="孔雀翎") b_unit="支";
        else b_unit="根";
        if (weapon->query("anqi/now") != 0) remain=weapon->query("anqi/now")-num_hit;
        else remain=0;
        weapon->set("anqi/now",remain);
        if (weapon->query("anqi/now") == 0) 
          {weapon->delete("anqi/type");  weapon->set("long",weapon->query("orilong"));}
        else weapon->set("long",weapon->query("orilong")+"里面已经装了"
           +chinese_number(weapon->query("anqi/now"))+b_unit+weapon->query("anqi/type")+"，想拆掉用uninstall。\n"); 

        if (hitt==0)
	  {
           msg += HIW "$n连忙身行一转，连退数步，闪过了这满天花雨般的一击。\n"NOR;
           message_vision(msg, me, target);
           me->start_busy(random(3));
/*
           if(!target->is_busy())
               target->start_busy(random(3));
*/
	  }
        else 
          {
	   damage=damage*hitt;
           target->receive_damage("kee",damage,me);
    if (random(damage)>target->query_temp("apply/armor"))  {
       target->receive_wound("kee",damage-target->query_temp("apply/armor"),me);
       wound=1;
  }
           msg += HIW "$n躲闪不及，身上"+chinese_number(hitt)+HIW "处中了"+anqi_type+"！\n"NOR;
           message_vision(msg, me, target);
           write("\n");
     //      write(chinese_number(damage));
if (wizardp(me)) write (damage+"\n");
      //     write("\n");
       me->start_busy(random(2));
     COMBAT_D->report_status(target,wound);
           if(!target->is_busy())
           target->start_busy(random(5));
           }
        msg = HIW "$n对着$N高声骂道：好啊，敢放暗器，看我怎么收拾你！\n" NOR;     
        message_vision(msg, me, target);
        target->kill_ob(me);
      me->set_temp("chaofeng_busy",1);
    call_out("remove_effect",3+random(5),me);
        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("chaofeng_busy");
}
