// cracked by vikee 2/09/2002   vikee@263.net

// bula and mon@xyj

inherit __DIR__"yaoguai.c";

// here should be this NPC specific skills.

void set_skills(int j, int level)
{
        object me=this_object();
        object weapon;

        me->set("title","火云洞头目");
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
 
        me->set_skill("stick", j+random(15));
        me->set_skill("dali-bang", j+random(15));
        me->set_skill("fork",j+random(15));
        me->set_skill("yueya-chan",j+random(15));
        me->set_skill("moshenbu", j+random(15));
        me->set_skill("moyun-shou", j+random(15));
        me->set_skill("huomoforce", j+random(15));
        me->set_skill("pingtian-dafa", j+random(15));
		me->set_skill("spear", j+random(15));
		me->set_skill("huoyun-qiang", j+random(15));

        me->map_skill("force", "huomoforce");
        me->map_skill("stick", "dali-bang");
        me->map_skill("fork","yueya-chan");
        me->map_skill("parry", "dali-bang");
        me->map_skill("spells", "pingtian-dafa");
        me->map_skill("dodge", "moshenbu");
        me->map_skill("unarmed", "moyun-shou");
		me->map_skill("spear", "huoyun-qiang");

	set("chat_chance_combat", cast_chance(level));
        set("chat_msg_combat", ({
       (: perform_action,"stick", "shenli" :),
//        (: cast_spell, "gouhun" :),
        (: exert_function, "fire" :),
        }) );

     //   if (random(2))
     //      weapon=new("/d/obj/weapon/axe/huafu");
       // else
           weapon=new("/d/obj/weapon/stick/xiangmo");
        weapon->move(me);
        carry_object("/d/obj/cloth/shoupiqun")->wear();
        command("wield all");
}