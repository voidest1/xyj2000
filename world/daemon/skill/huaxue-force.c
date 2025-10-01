// cracked by vikee 2/09/2002   vikee@263.net

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return notify_fail("鍖栬绁炲姛鍙兘鍚戝笀鐖跺锛屾垨鏄粠杩愮敤(exert)涓鍔犵啛缁冨害銆俓n");
}
string exert_function_file(string func)
{
        return CLASS_D("yaomo") + "/bibotan/huaxie-force/" + func;
}