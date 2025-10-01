// cracked by vikee 2/09/2002   vikee@263.net
// rose_poison.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        me->receive_wound("sen", 20);
        me->apply_condition("mihun_poison", duration - 1);
        tell_object(me, HIR "浣犺寰楀洓鑲㈤夯鏈紝韬綋涓殑鍏冪姝ｄ竴鐐圭偣鐨勬祦澶憋紟\n" NOR);
        if( duration < 1 ) return 0;
        return 1;
}