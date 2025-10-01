// cracked by vikee 2/09/2002   vikee@263.net
// dao
inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
        if( (int)me->query_skill("spells", 1) < 20
        ||      (int)me->query_skill("spells") <= (int)me->query_skill("baguazhou") )
                return
notify_fail("浣犵殑娉曟湳淇负杩樹笉澶熼珮娣憋紝鏃犳硶瀛︿範鍏崷鍜掞紟\n");
        return 1;
}

/*
string cast_spell_file(string spell)
{
        return CLASS_D("fighter") + "/baguazhou/" + spell;
}
*/

string scribe_spell_file(string spell)
{
        return CLASS_D("fighter") + "/baguazhou/" + spell;
}

string type() { return "magic"; }