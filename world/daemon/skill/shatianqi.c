// cracked by vikee 2/09/2002   vikee@263.net
// wuxiangforce.c
inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return
notify_fail("鐓炲ぉ姘斿彧鑳界敤瀛︾殑锛屾垨鏄粠杩愮敤(exert)涓鍔犵啛缁冨害銆俓n");
}
string exert_function_file(string func)
{
        return CLASS_D("yaomo") + "/shatianqi/" + func;
}