// cracked by vikee 2/09/2002   vikee@263.net
//modified by sgzl for dntg/donghai quest
#include <skill.h>

inherit NPC;
inherit F_MASTER;

string expell_me(object me);
int donghai_quest(object who);

void create()
{
       	set_name("°½¹ã", ({"ao guang", "ao","guang","longwang","wang"}));

	set("long","°½¹ãÊÇ¶«º£µÄÁúÍõ£¬ÆäĞÖµÜ·Ö±ğÕÆ¹Ü¶«£¬Î÷£¬ÄÏ£¬±±ËÄº£¡£
ÓÉÓàÆäË®×åÖÚ¶à£¬ÉùÊÆºÆ´ó£¬Ù²È»¶À°ÔÒ»·½¡£\n");
       	set("gender", "ÄĞĞÔ");
       	set("age", 66);
	set("title", "¶«º£ÁúÍõ");
	set("class","dragon");
       	set("attitude", "peaceful");
       	set("shen_type", 1);
        set("combat_exp", 1260000);
        set("daoxing", 1500000);

        set("rank_info/respect", "±İÏÂ");
       	set("per", 20);
       	set("str", 30);
       	set("max_kee", 3000);
       	set("max_gin", 400);
       	set("max_sen", 1500);
       	set("force", 3000);
       	set("max_force", 1500);
       	set("force_factor", 120);
       	set("max_mana", 800);
       	set("mana", 1600);
       	set("mana_factor", 40);
       	set("combat_exp", 1200000);
        set("daoxing", 1500000);

	set_skill("huntian-hammer", 180);
	set_skill("hammer", 180);
	set_skill("literate", 100);
       	set_skill("unarmed", 200);
       	set_skill("dodge", 180);
       	set_skill("force", 180);
       	set_skill("parry", 180);
       	set_skill("fork", 180);
       	set_skill("spells", 170);
	set_skill("seashentong", 170);
	set_skill("dragonfight", 200);
	set_skill("dragonforce", 180);
	set_skill("fengbo-cha", 180);
	set_skill("dragonstep", 180);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");

        set("inquiry", ([ 
           "Àë¹¬": (: expell_me :),
	   "leave": (: expell_me :), 
           "±øÆ÷": (: donghai_quest :),
           "weapon": (: donghai_quest :), 
        ]) );

        create_family("¶«º£Áú¹¬", 1, "Ë®×å");
	set_temp("apply/armor",50);
	set_temp("apply/damage",25);
	setup();

        carry_object("/d/sea/obj/longpao")->wear();
}
void init()
{
	::init();
	add_action("do_agree", "agree");
	add_action("do_learn", "xuexi");
}


void destroy(object ob)
{
        destruct(ob);
        return;
}

void unsetlearn(object ob)
{
	if (find_player(ob->query("id"))) {
		ob->set_temp("temp/learn", 0);
		ob->save();
		}
}


string *reject_msg = ({
	"ËµµÀ£ºÄúÌ«¿ÍÆøÁË£¬ÕâÔõÃ´¸Òµ±£¿\n",
	"ÏñÊÇÊÜ³èÈô¾ªÒ»Ñù£¬ËµµÀ£ºÇë½Ì£¿ÕâÔõÃ´¸Òµ±£¿\n",
	"Ğ¦ÖøËµµÀ£ºÄú¼ûĞ¦ÁË£¬ÎÒÕâµãµñ³æĞ¡¼¼Ôõ¹»×Ê¸ñ¡¸Ö¸µã¡¹ÄúÊ²Ã´£¿\n",
});

int do_learn(string arg)
{
	string skill, teacher, master;
	object me= this_player(), ob;
	int master_skill, my_skill, sen_cost;

	if(!arg || sscanf(arg, "%s from %s", skill, teacher)!=2 )
		return notify_fail("Ö¸Áî¸ñÊ½£ºxuexi <¼¼ÄÜ> from <Ä³ÈË>\n");

	if( me->is_fighting() )
		return notify_fail("ÁÙÕóÄ¥Ç¹£¿À´²»¼°À²¡£\n");

	if( !(ob = present(teacher, environment(me))) || !ob->is_character())
		return notify_fail("ÄãÒªÏòË­Çó½Ì£¿\n");

	if( !living(ob) )
		return notify_fail("àÅ£®£®£®ÄãµÃÏÈ°Ñ" + ob->name() + "ÅªĞÑÔÙËµ¡£\n");

	if( !master_skill = ob->query_skill(skill, 1) )
		return notify_fail("ÕâÏî¼¼ÄÜÄã¿ÖÅÂ±ØĞëÕÒ±ğÈËÑ§ÁË¡£\n");

	if (skill != "unarmed" || !me->query_temp("temp/learn") ) 
		return notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );

	notify_fail(ob->name() + "²»Ô¸Òâ½ÌÄãÕâÏî¼¼ÄÜ¡£\n");
	if( ob->prevent_learn(me, skill) )
		return 0;

	my_skill = me->query_skill(skill, 1);
	if( my_skill >= master_skill )
		return notify_fail("ÕâÏî¼¼ÄÜÄãµÄ³Ì¶ÈÒÑ¾­²»ÊäÄãÊ¦¸¸ÁË¡£\n");

	notify_fail("ÒÀÄãÄ¿Ç°µÄÄÜÁ¦£¬Ã»ÓĞ°ì·¨Ñ§Ï°ÕâÖÖ¼¼ÄÜ¡£\n");
	if( !SKILL_D(skill)->valid_learn(me) ) return 0;

	sen_cost = 250 / (int)me->query_int();

	if( !my_skill ) {
		sen_cost *= 2;
		me->set_skill(skill,0);
	}

	if( (int)me->query("learned_points") >= (int)me->query("potential") )
		return notify_fail("ÄãµÄÇ±ÄÜÒÑ¾­·¢»Óµ½¼«ÏŞÁË£¬Ã»ÓĞ°ì·¨ÔÙ³É³¤ÁË¡£\n");
	printf("ÄãÏò%së½ÌÓĞ¹Ø¡¸%s¹µÄÒÉÎÊ¡£\n", ob->name(),
		to_chinese(skill));

	if( ob->query("env/no_teach") )
		return notify_fail("µ«ÊÇ" + ob->name() + "ÏÖÔÚ²¢²»×¼±¸»Ø´ğÄãµÄÎÊÌâ¡£\n");

	tell_object(ob, sprintf("%sòÄãÇë½ÌÓĞ¹Ø¡¸%s¹µÄÎÊÌâ¡£\n",
		me->name(), to_chinese(skill)));

	if( (int)ob->query("sen") > sen_cost/5 + 1 ) {
		if( userp(ob) ) ob->receive_damage("sen", sen_cost/5 + 1);
	} else {
		write("µ«ÊÇ" + ob->name() + "ÏÔÈ»Ì«ÀÛÁË£¬Ã»ÓĞ°ì·¨½ÌÄãÊ²Ã´¡£\n");
		tell_object(ob, "µ«ÊÇÄãÌ«ÀÛÁË£¬Ã»ÓĞ°ì·¨½Ì" + me->name() + "¡£\n");
		return 1;
	}
		

	if( (int)me->query("sen") > sen_cost ) {
		if( (string)SKILL_D(skill)->type()=="martial"
		&&	my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) {
			printf("Ò²ĞíÊÇµÀĞĞ²»¹»£¬Äã¶Ô%sÄ»Ø´ğ×ÜÊÇÎŞ·¨Áì»á¡£\n", ob->name() );
		} else {
			printf("ÄãÌıÁË%sÄÖ¸µ¼£¬ËÆºõÓĞĞ©ĞÄµÃ¡£\n", ob->name());
			me->add("learned_points", 1);
			me->improve_skill(skill, random(me->query_int()));
		}
	} else {
		sen_cost = me->query("sen");
		write("Äã½ñÌìÌ«ÀÛÁË£¬½á¹ûÊ²Ã´Ò²Ã»ÓĞÑ§µ½¡£\n");
	}

	me->receive_damage("sen", sen_cost );

	return 1;
}

void attempt_apprentice(object ob)
{	
	if( (int)ob->query_skill("dragonforce",1) < 50
	|| (int)ob->query_skill("seashentong", 1) < 50) {
	command("say " + RANK_D->query_respect(ob) +
		"»¹ÊÇÏÈµ½´ó½«¾ü»òĞ¡Å®´¦°Ñ»ù´¡´òºÃÁËÔÙÀ´ÎÒÕâ¶ù°É¡£\n");
	return;
	}	
        command("smile");
        command("say ÄÑµÃ" + RANK_D->query_respect(ob) +
		"ÓĞ´ËĞÄÖ¾£¬»¹ÍûÈÕºó¶à¼ÓÅ¬Á¦£¬ÎªÎÒ¶«º£Áú¹¬Õù¹â¡£\n");
        command("recruit " + ob->query("id") );
	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "dragon");
}

string expell_me(object me)
{
  me=this_player();
  if((string)me->query("family/family_name")=="¶«º£Áú¹¬")
    {
      me->set_temp("betray", 1);
      command("sigh");
      return ("ÄãÒªÀë¿ªÎÒÒ²²»ÄÜÇ¿Áô¡£Ö»ÊÇ°´ÎÒ¶«º£¹æ¾Ø£¬È´ĞëÊÜ·£¡£
¿ÖÅÂ¼ÈÊÇÉí·ÇÁúÀà£¬ÕâÁúÉñĞÄ·¨Óë²©»÷²¢²»ÄÜÈçÇ°°ãÔË×ª£¬Äã¿ÉÔ¸Òâ(agree)?\n");
    }
  return ("È¥ÎÊÎÊÔ¬ÏÈÉú°É£¬»òĞíËûÖªµÀ£¡\n");
}

int do_agree(string arg)
{
  object me;
  me = this_player();
  if(me->query_temp("betray"))
    {
      message_vision("$N´ğµÀ£ºµÜ×ÓÔ¸Òâ¡£\n\n", me);
      command("say ÈË¸÷ÓĞÖ¾£¬¼ÈÊÇ" + RANK_D->query_respect(me) +
        "²»Ô¸ÁôÔÚ¶«º££¬¾ÍÇë³ö¹¬È¥°É¡£Ö»ÊÇ½­ºşÏÕ¶ñ£¬" + RANK_D->query_respect(me) +
	"µ±ºÃ×ÔÎªÖ®¡£¡£¡£\n");
      me->set_skill("dragonforce", (int)me->query_skill("dragonforce",1)/2);
      me->set_skill("dragonfight", (int)me->query_skill("dragonfight",1)/3);
      me->set("combat_exp", me->query("combat_exp")*80/100);
      me->set("daoxing", me->query("daoxing")*80/100);
      me->delete("family");
      me->delete("class");
      me->set("title", "ÆÕÍ¨°ÙĞÕ");
      me->set_temp("betray", 0);
      me->add("betray/count", 1);
      me->add("betray/longgong", 1);
      me->save();
      return 1;
    }
  return 0;
}

int donghai_quest(object who)
{
  object me=this_object();
  object fighter;
  string weapon_name,weapon_id,weapon_unit,temp_flag;

  who=this_player();
  if (who->query("dntg/donghai")=="done") {
    message_vision("$NÃæÉ«²Òµ­£¬²»ÇéÔ¸µØËµ£º¡°ÄÇÉñ±ø»¹ÔÚÀÏµØ·½£¬ÇÒËæÎÒÀ´¡£¡±\n",this_object());
    call_out("sendto_maze",2,who);
    return 1;
  }

  if (
      who->query("dntg/donghai") == "begin"
      || who->query("dntg/donghai") == "da kan dao"
      || who->query("dntg/donghai") == "jiu gu cha"
      || who->query("dntg/donghai") == "mei hua chui"
     )

    {
        if (who->query("dntg/donghai") == "begin")
           {weapon_name="´ó¿³µ¶"; weapon_id="da kan dao";weapon_unit="±ú";temp_flag="try_dao";}
        if (who->query("dntg/donghai") == "da kan dao")
           {weapon_name="¾Å¹É²æ"; weapon_id="jiu gu cha";weapon_unit="Ö§";temp_flag="try_cha";}
        if (who->query("dntg/donghai") == "jiu gu cha")
           {weapon_name="Ã·»¨´¸"; weapon_id="mei hua chui";weapon_unit="¶Ô";temp_flag="try_chui";}
        if (who->query("dntg/donghai") == "mei hua chui")
           {weapon_name="»­¸Ëêª"; weapon_id="hua gan ji";weapon_unit="±ú";temp_flag="try_ji";}

        
        if (present(weapon_id, this_player()) && present("ye cha", environment()))
          message_vision("ÁúÍõµÀ£ºÄúÏÈÄÃÕâ"+weapon_name+"ºÍÒ¹²æÁ·Á·°É£¡\n",me);
        else if (present(weapon_id, environment()) && present("ye cha", environment()))
          message_vision("ÁúÍõµÀ£ºÄúÏÈÄÃÕâ"+weapon_name+"ºÍÒ¹²æÁ·Á·°É£¡\n",me);
        else if (present(weapon_id, this_player()) || present(weapon_id, environment()))
          {
          message_vision("¶«º£ÁúÍõËµµÀ£ºÈÃÎÒÕÒ¸öÈËÏÈÅãÄúÁ·Á·£¿\n",me);
          message_vision("¶«º£ÁúÍõÒ»ÕĞÊÖ£¬Ò»¸öÒ¹²æ×ßÁË¹ıÀ´¡£\n",me);
          fighter = new ("/d/dntg/donghai/npc/fighter");
          fighter->move(environment(me));
          } 
        else if (present("ye cha", environment()))
          message_vision("ÁúÍõµÀ£º²»ÖªÄÇ"+weapon_name+"±»Ë­ÄÃÈ¥ÁË£¡\n",me);
        else
          {
          message_vision("$NÁ¬Ã¦ÆğÉíËµµÀ£º"+RANK_D->query_respect(who)+"ÉÔºî£¬´ıÎÒÏëÏë£¿\n",me,who);
          message_vision("ÎÒÕâÁú¹¬ÖĞÓĞ"+weapon_unit+weapon_name+"»¹´ÕºÏ×ÅÄÜÊ¹£¬"+RANK_D->query_respect(who)+"Èô²»ÏÓÆú£¬¾ÍËÍÓë"+RANK_D->query_respect(who)+"ÓÃ°É£¡\n",who);
          who->set_temp("dntg/donghai",temp_flag);
          call_out ("fight_quest",2,who);
          }
        return 1;
    } 

  else if (who->query("dntg/donghai") == "hua gan ji" )
    {
    me->command("consider");
    message_vision("´Óºó¹¬ÅÜÀ´Ò»¸öÁúÆÅ£¬ÔÚÁúÍõ¶ú±ßĞ¡ÉùËµÁË¼¸¾ä»°¡£\n",me);
    call_out ("sendto_maze",3,who);
    return 1;
    }
   command("nod");
  message_vision("$NÀÁÑóÑóµÄËµ£º¡°Òª±øÆ÷°¡£¿°ÁÀ´¹úÓĞµÄÊÇ£¬È¥ÄÇÀïÅªĞ©°É¡£¡±\n",me);
  message_vision("$N¶ÙÁË¶Ù£¬ÓÖËµ£º¡°ÎÒÁú¹¬µÄ±øÆ÷£¬ÁÂÄãÃÇÕâĞ©·²·òË××ÓÒ²Ê¹²»ÁË¡£¡±\n",me);
  command("wave");
  return 1;
}

void fight_quest (object who)
{
  object me=this_object();
  object fighter,fa_bao;
  string weapon_name,weapon_id,weapon_unit;


  if (who->query("dntg/donghai") == "begin")
    {weapon_name="´ó¿³µ¶"; fa_bao = new ("/d/dntg/donghai/obj/dakandao");weapon_unit="±ú";}
  if (who->query("dntg/donghai") == "da kan dao")
    {weapon_name="¾Å¹É²æ"; fa_bao = new ("/d/dntg/donghai/obj/jiugucha");weapon_unit="Ö§";}
  if (who->query("dntg/donghai") == "jiu gu cha")
    {weapon_name="Ã·»¨´¸"; fa_bao = new ("/d/dntg/donghai/obj/meihuachui");weapon_unit="¶Ô";}
  if (who->query("dntg/donghai") == "mei hua chui")
    {weapon_name="»­¸Ëêª"; fa_bao = new ("/d/dntg/donghai/obj/huaganji");weapon_unit="±ú";}

  message_vision("¶«º£ÁúÍõÒ»ÕĞÊÖ£¬Ò»¸öÒ¹²æÌ§¹ıÒ»"+weapon_unit+weapon_name+"¡£\n",me);
  fighter = new ("/d/dntg/donghai/npc/fighter");
  fighter->move(environment(me));
  fa_bao->move(environment(me));
  message_vision("¶«º£ÁúÍõËµµÀ£º£¢ÒªÎÒÒªºÍÎÒµÄÊÖÏÂÏÈÁ·Á·£¿£¢\n",me);
}

void sendto_maze (object who)
{
  object me=this_object();
  message_vision("$NËµµÀ£º"+RANK_D->query_respect(who)+"Îä¹¦¸ÇÊÀ£¬¿Éµ½ºóÃæµÄº£²ØÖĞÊÔÒ»ÊÔ¶¨º£ÉñÕëÌú¡£\n",me,who);
  call_out ("send_maze",3,who);
}

void send_maze (object who)
{
  object me=this_object();
  message_vision("Ëµ×Å£¬¶«º£ÁúÍõ°Ñ$NËÍµ½ÁËÒ»¸öµØ·½¡£\n",who);
  who->move("/d/dntg/donghai/haidimigong");
  message_vision("$NÒ»¹°ÊÖµÀ£º"+RANK_D->query_respect(who)+"ÏòÇ°×ß¼´¿É¿´µ½ÄÇÉñÌú£¬Ë¡ÀÏ·ò²»·îÅãÁË¡£\n",me,who);
  message_vision("Ëµ°Õ£¬ÁúÍõ×ªÉí»Ø¹¬ÁË¡£\n",me);
}

