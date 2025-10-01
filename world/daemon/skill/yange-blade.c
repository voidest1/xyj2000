// cracked by vikee 2/09/2002   vikee@263.net
// spring-blade.c

/*
雁歌刀法    dodge  -10    parry  0    damage  20
雁歌刀法刀势奔放，为豪侠悲歌之士所喜。此刀法以气势
逼人，而不在乎能否杀伤杀死敌手。
*/

inherit SKILL;

mapping *action = ({
        ([      "action":
"$N一招「山川萧条」，手中$w卷起一股狂风，挥向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "割伤"
        ]),
        ([      "action":
"$N手中$w一晃，由下至上撩向$n的$l，一招「孤城落日」使得恰到好处",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "划伤"
        ]),
        ([      "action":
"$N眼神恍惚，手中$w飘摇不定，一招「大漠穷秋」斜斜的砍向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "砍伤"
        ]),
        ([      "action":
"$N左手执着$w，右手扶着刀背用力推出，一招「力尽关山」扫向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "砍伤"
        ]),
        ([      "action":
"$N冷笑一声，一招「边风飘摇」，手中$w带者丝丝冷风由下至上划向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "划伤"
        ]),
        ([      "action":
"$N狂喝一声，使出一招「绝域苍茫」，双手紧握$w
带着逼人的杀气，刺向$n的$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "刺伤"
        ]),
		([      "action":
"$N义无反顾的使出一招「塞雁南飞」，手中$w
带着雄浑的悲壮，如同不归的飞雁，砍向$n的$l",
                "damage":               150,
                "dodge":                -20,
                "parry":                -20,
                "damage_type":  "砍伤"
        ]),
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 80 )
                return
notify_fail("你的内力不够，没有办法学雁歌刀法。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
                return
notify_fail("你必须先找一把刀才能学雁歌刀法。\n");

        return 1;
}

int valid_enable(string usage)
{
        return (usage=="blade") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
      //  return action[random(sizeof(action))];
	int i;
	i=me->query_temp("yange_perform");
	if( !me->query_temp("yange_perform")) {
                return action[random(7)];
	}else {
		return action[i];}
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "blade" )
                return notify_fail("你必须先找一把刀，才能练刀法。\n");

        if( (int)me->query("kee") < 40 )
                return
notify_fail("你的体力不够练这门刀法，还是先休息休息吧。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        return 1;
}

string perform_action_file(string func) {
  return CLASS_D("zhenyuan") + "/yange-blade/" + func;
}
