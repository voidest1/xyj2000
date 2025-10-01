// cracked by vikee 2/09/2002   vikee@263.net
// dao
inherit SKILL;


int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
        if( (int)me->query_skill("spells", 1) < 20 )
        return notify_fail("浣犵殑娉曟湳淇负杩樹笉澶熼珮娣憋紝鏃犳硶瀛︿範鍖栬澶ф硶銆俓n");
        return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("yaomo") + "/bibotan/huaxue-dafa/" + spell;
}