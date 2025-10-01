// cracked by vikee 2/09/2002   vikee@263.net
//puti.c
inherit NPC;
inherit F_MASTER;

void create()
{
  set_name("µØ²ØÍõÆĞÈø", ({"dizang pusa", "pusa"}));
  set("long", "ÃæÈçÖìÓñ£¬´ó¶ú´¹¼ç£¬Ò»Á³Ëà¾²£®
Ëû±ãÊÇÖ÷¹ÜÒõ²ÜµØ¸®£¬ÌìÏÂ¹í»êµÄµØ²ØÍõÆĞÈø£®\n");
  set("gender", "ÄĞĞÔ");
  set("class", "youling");
  set("age", 70);
  set("attitude", "friendly");
  set("shen_type", 1);
  set("per", 30);
  set("str", 30);
  set("int", 30+random(5));
  set("max_kee", 3000);
  set("max_gin", 2500);
  set("max_sen", 2000);

  set("force", 5000);
  set("max_force", 3000);
  set("force_factor", 120);
  set("max_mana", 3000);
  set("mana", 5000);
  set("mana_factor", 120);

  set("combat_exp", 2000000);
  set("daoxing", 4000000);

  set_skill("stick", 180);
  set_skill("kusang-bang", 180);
  set_skill("unarmed", 180);
  set_skill("whip", 180);
  set_skill("hellfire-whip", 200);
  set_skill("dodge", 180);
  set_skill("parry", 180);
  set_skill("literate", 150);
  set_skill("spells", 200);
  set_skill("force", 180);
  set_skill("tonsillit", 150);
  set_skill("ghost-steps", 180);
  set_skill("gouhunshu", 180);
  set_skill("jinghun-zhang", 180);
  set_skill("zhuihun-sword", 180);
  set_skill("sword", 180);

  map_skill("sword", "zhuihun-sword");
  map_skill("force", "tonsillit");
  map_skill("unarmed", "jinghun-zhang");
  map_skill("dodge", "ghost-steps");
  map_skill("spells", "gouhunshu");
  map_skill("parry", "hellfire-whip");
  map_skill("whip", "hellfire-whip");
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: cast_spell, "gouhun" :),
		(: cast_spell, "inferno" :),
		(: cast_spell, "invocation" :),
        }) );
  set("nk_gain", 600);
	
  set_temp("apply/armor", 50);
  set_temp("apply/dodge", 50);

  
  create_family("ÑÖÂŞµØ¸®", 1, "ÄãºÃ");
  setup();
  
  carry_object("/d/obj/cloth/baipao")->wear();
  carry_object("/d/obj/weapon/whip/longsuo")->wield();
}

void attempt_apprentice(object ob, object me)
{
  if ( (string)ob->query("family/family_name")=="ÑÖÂŞµØ¸®") {
    if (((int)ob->query("combat_exp") < 350000 )) {
      command("say " + RANK_D->query_rude(ob) + "ÕâµãÈı½ÅÃ¨µÄ°ÑÊ½Ò²¸Òµ½ÎÒÕâÀï¶ªÈËÏÖÑÛ£¿");
      return;
    }
    command("grin");
    command("say ºÜºÃ£¬" + RANK_D->query_respect(ob) +
	    "¶à¼ÓÅ¬Á¦£¬ËûÈÕ±Ø¶¨ÓĞ³É¡£\n");
    command("recruit " + ob->query("id") );
    return;
  }
  command("shake");
  command("say " + RANK_D->query_respect(ob) +
	  "»¹ÊÇÏÈÈ¥Ñ§Ğ©»ù´¡¹¦·ò°É£¡\n");
  return;
}


ÿ
