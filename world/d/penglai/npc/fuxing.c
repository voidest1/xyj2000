// cracked by vikee 2/09/2002   vikee@263.net
//∫£…œ»˝–«

inherit NPC;
string ask_me();
void create()
{
        set_name("∏£–«", ({"fu xing", "xing"}));
	set("title", "≈Ó¿≥»˝¿œ");
	set("gender", "ƒ––‘");
	set("long", "œˆ∫∫÷–º‰“ª¿œ»À£¨ ÷≈ı»Á“‚∑…∞™–Â°£∫˘¬´≤ÿ–ÓÕÚƒÍµ§£¨±¶◊≠√˚ È«ßºÕ Ÿ°£
∂¥¿Ô«¨¿§»Œ◊‘”…£¨∫¯÷–»’‘¬ÀÊ≥…æÕ°£Â€”ŒÀƒ∫£»Œ«Âœ–£¨…¢µ≠ Æ÷ﬁ»›∏£Î–°£
‘¯∏∞Û¥Ã“◊Ìº∏‘‚£¨–— ±√˚‘¬ªπ“¿æ…°£∑Ω√Ê”Ò—’∂‡…Òø°£¨»˝¬∆≥§‹€∆ÆÚ¢±ﬂ°£\n");
        set("attitude", "peaceful");
        set("combat_exp", 800000);
	set("daoxing", 1500000);

	create_family("ŒÂ◊Øπ€", 2, "µ‹◊”");
	set("age", 70);
	set("per", 100);
        set("str", 30);
        set("int", 30);
        set("cor", 30);
        set("cps", 30);
        set("con", 30);
	set("class", "xian");
	set("rank_info/respect", "¿œ∏£–«");
	set("max_kee", 1000);
	set("max_sen", 1000);
	set("force", 1000);
	set("max_force", 1000);
	set("force_factor", 40);
	set("max_mana", 600);
	set("mana",600);
	set("mana_factor", 50);
	
	set_skill("spells", 120);
	set_skill("taiyi", 120);
	set_skill("force",120);
	set_skill("zhenyuan-force",120);
	set_skill("parry", 120);
	set_skill("dodge", 120);
	set_skill("baguazhen", 100);
	set_skill("unarmed", 100);
	set_skill("wuxing-quan", 100);
	set_skill("sword",110);
	set_skill("xiaofeng-sword",120);
	set_skill("blade",110);
	set_skill("yange-blade",120);

	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("dodge", "baguazhen");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "xiaofeng-sword");
	map_skill("blade", "yange-blade");

        set("inquiry", ([
		"±Ã≈∫"     : "Œ“√ªƒ«ÕÊ“‚£¨»•Œ Œ ¿œ Ÿ–«∞…£°\n",
                "Ωª¿Ê"     : "Œ“√ªƒ«ÕÊ“‚£¨»•Œ Œ ¿œ¬ª–«∞…£°\n",
		"name"     : "¿œ∑Ú∏£–« «“≤°£\n",
		"here"     : "¥ÀƒÀ≈Ó¿≥œ…µ∫“≤°£\n",
		"œ¬∆Â"	   : "ƒ„∏ˆ≥Ù∆Â¬®◊”£¨À≠“™∏˙ƒ„œ¬∆Â£°\n",
		"Œß∆Â"     : "¡¨Œß∆Â∂º≤ª÷™µ¿£ø\n",
                "ª‘Ê"     : (: ask_me :),
        ]));

	setup();
	carry_object("/d/obj/cloth/bai")->wear();	
	carry_object("/d/penglai/npc/obj/bag");

	// mon 7/19/98
	// first fruit generated after the xing refresh
	// for a while.
	set("time", 0);
	call_out("reg", 1500+random(500));
}

string ask_me()
{
        object ob;
	        
	if((int)this_player()->query("combat_exp") < 30000 )
		return "√ªº˚¿œ∑Ú’˝œ¬∆Âƒÿ¬£¨“‘∫Û‘ŸÀµ∞…£°\n";

	// added by snowcat on 6/22/1997
	if (this_object()->is_fighting())
		return "√ªº˚¿œ∑Ú’˝¥Ú◊≈¬£¨“‘∫Û‘ŸÀµ∞…£°\n";

	if ( present("huo zao", this_player()) )
		return "≥‘£¨≥‘£¨≥‘£¨≈÷µƒ∂ºœÛ÷Ì¡À£°\n";

        if ( present("huo zao", environment()) )
		return "ƒ«≤ª «”–“ªøÈƒÿ¬Ô£¨≥‘ÕÍ‘ŸÀµ£°\n";

	if (query("last_winner") == this_player()->query("id") &&
	    random(5)) {
	    	set("noask",1);
	        call_out("ref", 20);
		return "≤ª«…£¨≤ª«…£¨Œ““≤√ª¡À£°\n";
	}	
	
	if(query("time") <1 || query("noask"))
		return "≤ª«…£¨≤ª«…£¨Œ““≤√ª¡À£°\n";

		say("∏£–«Àµµ¿£∫ƒ«µΩ“™«∆ƒ„πª≤ªπª∏Ò≥‘¡À£¨∑≈¬Ìπ˝¿¥∞…£°\n");
		this_player()->set_temp("shouxing_fight", 1);
		return ("∫Ÿ∫Ÿ£°\n");
}


int accept_fight(object who)
{
  	object me;
 	me = this_object();
  	if (!who->query_temp("shouxing_fight")){
		command("say ≤ª¥Ú≤ª¥Ú£¨√ªº˚¿œ∑Ú’˝œ¬∆Âƒÿ¬£°\n");
    		return 0;
	}
	// added by snowcat on 6/22/1997
  	if (me->is_fighting()){
		command("say ≤ª¥Ú≤ª¥Ú£°\n");
    		return 0;
	}
	say("∏£–«–¶µ¿£∫¿œÕ∑◊”ªÓ¡Àº∏«ßƒÍ£¨À≠“≤≤ª≈¬£°\n");
	me->set("eff_kee", (int)me->query("max_kee"));
        me->set("kee", (int)me->query("max_kee"));
        me->set("eff_sen", (int)me->query("max_sen"));
        me->set("sen", (int)me->query("max_sen"));

  	who->set_temp("shouxing_fight",0);
  	remove_call_out("check_fight");
  	call_out("check_fight", 1, me, who);
  	return 1;
}

void player_win (object me, object who)
{
  	object obj;
  	// added by snowcat on 6/22/1997
	if (me->query("time")<=0)
		return;
	obj=new("/d/obj/drug/huozao");
	say("∏£–«Ãæ¡À“ªø⁄∆¯£∫ƒÍºÕ¥Û¡À£¨µΩµ◊∆¯¡¶ªπ «≤ªº√£°\n");
	say("»Á¥ÀŒ‰“’∏ﬂ«ø£¨’Ê «¡ÓŒ“µ»≈Â∑˛∞°£°\n");
	obj->move(who);
        me->add("time", -1);
	message_vision("∏£–«∂‘$Nπ˛π˛–¶µ¿£∫…Ó∏–∑®¡¶£¨ŒﬁŒÔø…“‘±Ìæ¥£¨Ãÿæﬂª‘Ê£¨–¶ƒ…£°\n", who);
	me->set("last_winner",who->query("id"));
	call_out("reg", 500+random(500));
}
int ref()
{
	object me=this_object();
	me->set("noask", 0);
	return 1;
}
int reg()
{
	object me=this_object();
	me->set("time", 1);
	return 1;
}
void player_lose (object me, object who)
{
  	string msg;
  	msg = RANK_D->query_respect(who);
	
	command("jump");
	say("∏£–«π˛π˛¥Û–¶£∫"+msg+"ƒ™“™≤ª∏ﬂ–À£¨ªÿ»•∫√∫√¡∑Œ‰∞…£¨¿¥»’∑Ω≥§¬Ô£°\n");
}
void check_fight (object me, object who)
{
  	int my_kee, whos_kee;
  	int my_max_kee, whos_max_kee;

	if(!who) return;
  	my_kee = me->query("kee");
  	whos_kee = who->query("kee");
  	my_max_kee = me->query("max_kee");
  	whos_max_kee = who->query("max_kee");

  	if (me->is_fighting()){
    		remove_call_out("check_fight");
    		call_out ("check_fight",1,me,who);
    		return;
  	}

  	if (!present(who, environment(me)))
    		return;

	// changed by snowcat on 6/24/1997
	// bug abuse: player can exert recover when fight stops, 
	//if ((my_kee*100/my_max_kee) <=(whos_kee*100/whos_max_kee) )
	//	player_win (me, who);
	//else player_lose (me, who);
	if ((my_kee*100/my_max_kee) <= 50)
		player_win (me, who);
	else if ((whos_kee*100/whos_max_kee) <= 50)
		player_lose (me, who);
}

void die()
{

        if( environment() ) {
        message("sound", "\n\n÷ªÃ˝“ª…˘∫◊√˘£¨∏£–«ªØ◊˜“ªµ¿∞◊π‚œÚÃÏ…œ÷±≥Â∂¯»•°£°£°£\n\n
∞Îø’÷–”–»Àπ˛π˛–¶¡Àº∏…˘°£°£°£\n\n", environment());
        }

        destruct(this_object());
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="ŒÂ◊Øπ€" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			command("say ≤ª∏“µ±£¨≤ª∏“µ±°£\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			command("say ∫«∫«£¨ «" + ob->query("family/master_name") + "¿œÕ∑µƒÕΩµ‹£¨ƒ«Œ“æÕ≤ªøÕ∆¯¡À°£\n");
			command("recruit " + ob->query("id") );
		}
		else 
		{
			if( ob->query_skill("taiyi", 1) >= 80 )
			{
				command("say ∫√£¨”–≥ˆœ¢£¨’‚∏ˆÕΩµ‹Œ“ ’œ¬¡À°£\n");
				command("recruit " + ob->query("id") );
			}
			else
			{
				command("say Œ“√«œ…º“◊Óø¥÷ÿœ…∑®£¨ƒ„ªπµ√‘⁄’‚∑Ω√Êœ¬ø‡π¶°£\n");
			}
		}
	}

	else
	{
		command("say ∫√£¨≤ªπ˝ƒ„ªπ «œ»’“∞Àœ…À˚√«¡∑“ª–©»Î√≈µƒπ¶∑Ú∞…°£\n");
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "xian");
}




ˇ
