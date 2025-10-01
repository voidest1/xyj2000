// cracked by vikee 2/09/2002   vikee@263.net
// iceshock.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	me->receive_damage("gin", 25);
	me->receive_wound("kee", 25);
	me->receive_damage("sen", 25);
        me->set_temp("death_msg","閹板繐鐦ㄩ幒灞剧槰閸欐垳缍斿璁崇啊閵嗕繐n");

	me->apply_condition("iceshock", duration - 1);

	tell_object(me, HIB "娴ｇ姳鑵戦惃鍕壈鐎垫帗甯夊В鎺戝絺娴ｆ粈绨￠敍涔梟" NOR );
	if( duration < 1 ) return 0;

	return CND_CONTINUE;
}