// cracked by vikee 2/09/2002   vikee@263.net
// moon_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	me->receive_wound("sen", duration);
	me->receive_damage("sen", duration);
	me->receive_damage("kee", duration);
	me->receive_wound("kee", duration);
	me->set_temp("death_msg","绮惧姏鑰楀敖鑰屾銆俓n");
	me->apply_condition("moon_poison", duration);
	if (duration >0 )
	tell_object(me, HIG "浣犳劅瑙夎韩浣撲竴鐐圭偣铏氬急涓嬪幓锛乗n" NOR );
	if( duration < 1 ) return 0;
	return 1;
}