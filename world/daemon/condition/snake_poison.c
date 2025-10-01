// cracked by vikee 2/09/2002   vikee@263.net
// snake_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
	me->receive_wound("kee", 10);
	me->receive_damage("sen", 10);
	me->set_temp("death_msg","铔囨瘨鍙戜綔姝讳簡銆俓n");
	me->apply_condition("snake_poison", duration - 1);
	tell_object(me, HIG "浣犱腑鐨勮泧姣掑彂浣滀簡锛乗n" NOR );
	if( duration < 1 ) return 0;
	return 1;
}