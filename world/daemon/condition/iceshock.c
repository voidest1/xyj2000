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
        me->set_temp("death_msg","鎰忓瘨鎺屾瘨鍙戜綔姝讳簡銆俓n");

	me->apply_condition("iceshock", duration - 1);

	tell_object(me, HIB "浣犱腑鐨勬剰瀵掓帉姣掑彂浣滀簡锛乗n" NOR );
	if( duration < 1 ) return 0;

	return CND_CONTINUE;
}