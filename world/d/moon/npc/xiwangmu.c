// cracked by vikee 2/09/2002   vikee@263.net
//xiwangmu.c
inherit NPC;
inherit F_MASTER;

void create()
{
       set_name("Î÷ÍõÄ¸", ({"xi wangmu", "xi", "wangmu","master"}));
       set("long", "Î÷»ªÖÁÃîÉúÒÁ´¨£¬ÄÂÍõ°ËÆï·ÃÀ¥ÂØ¡£\n");
       set("title", "ÔÂ¹¬×æÊ¦");
       set("gender", "Å®ÐÔ");
       set("age", 100);
       set("class","xian");
       set("attitude", "friendly");
       set("rank_info/respect", "ÀÏÌ«Ì«");
       set("cor", 30);
       set("per", 30);
	set("looking", "ÃæÉ«ºìÈó£¬ÂúÁ³¸£Ì¬¡£");
       set("max_kee", 4500);
       set("max_gin", 800);
       set("max_sen", 4500);
       set("force", 4000);
       set("max_force", 2000);
       set("force_factor", 125);
       set("max_mana", 2000);
       set("mana", 4000);
       set("mana_factor", 100);
       set("combat_exp", 2000000);
  set("daoxing", 5000000);

       set_skill("literate", 150);
       set_skill("unarmed", 180);
       set_skill("dodge", 180);
       set_skill("force", 180);
       set_skill("parry", 180);
       set_skill("sword", 200);
       set_skill("spells", 190);
	set_skill("moonshentong", 190);
	set_skill("baihua-zhang", 180);
	set_skill("moonforce", 180);
	set_skill("snowsword", 200);
	set_skill("moondance", 150);
	map_skill("spells", "moonshentong");
	map_skill("unarmed", "baihua-zhang");
	map_skill("force", "moonforce");
	map_skill("sword", "snowsword");
	map_skill("parry", "snowsword");
	map_skill("dodge", "moondance");
   set("inquiry",([
//    "pantao": (: ask_pantao :),
//    "ó´ÌÒÔ°":(:ask_pantao:),
  ]));
	set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "arrow" :),

               (: cast_spell,"mihun" :),
               (: cast_spell,"shiyue" :),
        }) );

create_family("ÔÂ¹¬", 1, "ºì");
setup();

        carry_object("/d/obj/cloth/tianyi.c")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void attempt_apprentice(object ob)
{
	if ( !((string)ob->query("gender")=="Å®ÐÔ")){
	   command("shake");
    	   command("say ÎÒÃÇÔÂ¹¬Ö»ÊÕÅ®Í½£¬ÕâÎ»" + RANK_D->query_respect(ob) + "»¹ÊÇÁíÇë¸ß¾Í°É¡£\n");
	   return;
	}

	if ( (string)ob->query("family/family_name")=="ÔÂ¹¬") {
    if ( (int)ob->query("combat_exp")+(int)ob->query("daoxing")<200000) {
	command("say " + RANK_D->query_respect(ob) +
"µÄµÀÐÐ²»¹»¸ßÉî£¬ÓÐÐ©¾øÑ§ÃØ·¨¿ÖÅÂÄÑÒÔÁìÎò¡£\n");
	return;
	}
        command("pat "+ob->query("id"));
        command("say ºÃ£¬Ï£Íû" + RANK_D->query_respect(ob) +
"¶à¼ÓÅ¬Á¦£¬°ÑÎÒÃÇÔÂ¹¬·¢Ñï¹â´ó¡£\n");
       command("recruit " + ob->query("id") );
	return;
	}
	command("shake");
	command("say " + RANK_D->query_respect(ob) +
"»¹ÊÇÏÈÈ¥Ñ§Ð©»ù´¡¹¦·ò°É¡£\n");
        return;
}
int accept_fight(object me)
{
	return 0;
}
ÿ
string ask_pantao() {return "ok.";}
string ask_pantao() {
    return " ";
} /*
  if (this_player()->query("dntg/pantao")=="done")
  {
    command("slogan "+this_player->query("id"));
    message_vision("$NºÝºÝµØµÉÁË$nÒ»ÑÛ¡£\n",this_object(),this_player());
    return "»¹ÏëÈ¥¹Üó´ÌÒÔ°£¿Ã»ÃÅ¶ù£¡";
  }
  if (this_player()->query_temp("dntg/pantao")=="doing")
    return "²»ÊÇÒÑ¾­ÈÃÄãÈ¥¹ÜÌÒÔ°ÁËÂð£¿»¹ÎÊÊ²Ã´£¿";
  this_player()->set_temp("dntg/pantao","doing");
  return "OK.";
}
*/