// cracked by vikee 2/09/2002   vikee@263.net
inherit NPC;
inherit F_MASTER;

int rank_me();

void create()
{
       set_name("ºìº¢¶ù", ({"honghai er","er"}));
	set("title", "Ê¥Ó¤´óÍõ");
	set("long", "Å£Ä§ÍõÓëÂŞÉ²Å®µÄ¶ù×Ó£¬ÓÚ»ğÑæÉ½ÖĞĞŞÁ¶ÁËÒ»ÉíºÃ±¾Áì¡£\n");
       set("gender", "ÄĞĞÔ");
       set("age", 16);
	set("per", 25);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("spi", 25);

       	set("attitude", "heroism");

        set("combat_exp", 1200000);
  set("daoxing", 1500000);

        set("eff_dx", -500000);
        set("nkgain", 500);

       	set("class","yaomo");
       	set("max_kee", 1600);
       	set("max_sen", 1600);
       	set("force", 2500);
       	set("max_force", 1600);
       	set("force_factor", 100);
       	set("max_mana", 1600);
       	set("mana", 2500);
       	set("mana_factor", 80);
       
	set_skill("unarmed", 150);
       	set_skill("dodge", 200);
       	set_skill("force", 150);
       	set_skill("parry", 150);
       	set_skill("spear", 180);
	set_skill("spells", 150);
 	set_skill("huoyun-qiang", 180);
	set_skill("moshenbu", 200);
	set_skill("moyun-shou", 150);
	set_skill("huomoforce", 180);
	set_skill("pingtian-dafa", 150);

	map_skill("force", "huomoforce");
	map_skill("spells", "pingtian-dafa");
	map_skill("unarmed", "moyun-shou");
	map_skill("dodge", "moshenbu");
	map_skill("parry", "huoyun-qiang");
	map_skill("spear", "huoyun-qiang");

	set("kusong/Teach_Hong", 1);
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: cast_spell, "sanmei" :),
	}));


	create_family("»ğÔÆ¶´", 2, "À¶");

        set("inquiry", ([
                "Ö°Î»": (: rank_me :),
]) );


        setup();
	carry_object("/d/nanhai/obj/huojianqiang")->wield();
        carry_object("/d/qujing/bibotan/obj/zhanpao")->wear();
}

void attempt_apprentice(object ob)
{       ob=this_player();

	if( (string)ob->query("family/family_name") == "»ğÔÆ¶´") {

		if( (int)ob->query("max_mana") > 200 
		&& (int)ob->query("max_force") > 200
		&& !(int)ob->query("kusong") ) {
	
		command("nod");
		command("recruit " + ob->query("id"));
		return ;
		}
	}
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "yaomo");
		ob->set("title", "¿İËÉ½§»ğÔÆ¶´Ğ¡Ñı");
		ob->set("kusong/Teach_Hong", 1);
	}
}


int rank_me()
{
	object me=this_player();
	int exp;
	exp=(int)me->query("combat_exp");

	if( (string)me->query("family/family_name") == "»ğÔÆ¶´"
	&& (string)me->query("family/master_id") == "honghai er"){

		
		if( exp <= 10000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´Ñ²É½Ğ¡Ñı");
		} else if(exp <= 50000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´ÏÈ·æ");
		} else if(exp < 100000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´½¡½«");
		} else if(exp <= 250000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´Ñ²É½´ó½«");
		} else if(exp <= 500000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´ÑıÍõ");
		} else if(exp <= 1000000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´Ä§Íõ");
		} else if(exp <= 1500000 ){
			me->set("title", "¿İËÉ½§»ğÔÆ¶´³¤ÀÏ");
		} else {
			me->set("title", "¿İËÉ½§»ğÔÆ¶´¶´Ö÷");
		}

		tell_object(me, "ºìº¢¶ù¶ÔÄãËµ£ºÄã¿ÉÒÔ×ö"+me->query("title")+"¡£\n");
		tell_room(environment(me),
"ºìº¢¶ù¶Ô"+me->query("name")+"Ëµ£ºÄã¿ÉÒÔ×ö"+me->query("title")+"¡£\n", ({me, me}));

	}
	return 1;
}
ÿ