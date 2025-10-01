// cracked by vikee 2/09/2002   vikee@263.net
// snowcat 12 14 1997

inherit NPC;

#include <obstacle.h>

#define DEBUG 0

#define LEVEL_NONE 0
#define LEVEL_ASKED 1

int reward_player ();
int recover_death ();

void create()
{
  set_name("ÈçÀ´·ğ", ({ "rulai fo", "rulai", "fo" }));
  set("title", "·ğ×æ¶àÍÓ°¢Ù¤ÍÓ");
  set("long", "´ó´È´ó±¯ÁéÉ½À×Òô¹ÅÉ²·ğ×æ¶àÍÓ°¢Ù¤ÍÓÈçÀ´·ğÒ¯¡£\n");
  set("gender", "ÄĞĞÔ");
  set("age", 10000);
  set("attitude", "peaceful");
  set("rank_info/self", "Æ¶É®");
  set("rank_info/respect", "·ğ×æÒ¯Ò¯");
  //set("class", "bonze");
  set("str",100);
  set("per",100);
  set("max_kee", 10000);
  set("max_gin", 10000);
  set("max_sen", 10000);
  set("force", 10000);
  set("max_force", 10000);
  set("force_factor", 500);
  set("max_mana", 10000);
  set("mana", 10000);
  set("mana_factor", 500);
  set("combat_exp", 4000000);
  set("daoxing", 10000000);

  set_skill("literate", 300);
  set_skill("spells", 300);
  set_skill("buddhism", 300);
  set_skill("unarmed", 300);
  set_skill("jienan-zhi", 300);
  set_skill("dodge", 300);
  set_skill("lotusmove", 300);
  set_skill("parry", 300);
  set_skill("force", 300);
  set_skill("lotusforce", 300);
  set_skill("staff", 300);
  set_skill("lunhui-zhang", 300);
  map_skill("spells", "buddhism");
  map_skill("unarmed", "jienan-zhi");
  map_skill("dodge", "lotusmove");
  map_skill("force", "lotusforce");
  map_skill("parry", "lunhui-zhang");
  map_skill("staff", "lunhui-zhang");
  set("chat_chance_combat", 80);
  set("chat_msg_combat", ({
   (: cast_spell, "bighammer" :),
  }) );
  set("inquiry", ([
    "die" : (: recover_death :),
    "death" : (: recover_death :),
    "recover" : (: recover_death :),
    "ÆğËÀ»ØÉú" : (: recover_death :),
    "¸´Éú" : (: recover_death :),
    "ËÀ" : (: recover_death :),
    "Éú" : (: recover_death :),
    "qujing" : (: reward_player :),
    "obstacle" : (: reward_player :),
    "obstacles" : (: reward_player :),
    "È¡¾­" : (: reward_player :),
    "¾­" : (: reward_player :),
  ]) );

  set("my_level",LEVEL_NONE);
  setup();
  carry_object("/d/obj/cloth/jia_sha")->wear();
}

void init ()
{
  add_action("do_back", "back");
}

void announce (object me, string str)
{
  if (DEBUG)
  { 
    object snowcat = find_player ("snowcat");
    if (snowcat && wizardp(snowcat))
      tell_object (snowcat,"¡ô "+str+"\n");
  }
  else
  {
    CHANNEL_D->do_channel(me,"chat",str);
  }
}

int recover_death()
{
  object me = this_object();
  object who = this_player();

  if (who->query("obstacle/mud_age") > who->query("death/mud_age"))
  {
    message_vision ("$N¶Ô$nÒ¡ÁËÒ¡Í·£ºÀÏ·òÎ´ÎÅËÀÑ¸Ò²¡£\n",me,who);
    return 1;
  }
  if (! who->query("obstacle/reward"))
  {
    message_vision ("$N¶Ô$nÒ¡ÁËÒ¡Í·£ºÄãÏÈÈ¥Î÷Óò¹ı¹Ø°É¡£\n",me,who);
    return 1;
  }
  if (who->query("obstacle/rebirth") >= 3)
  {
    message_vision ("$N¶Ô$nÒ¡ÁËÒ¡Í·£ºÄãÈı¸ù¾ÈÃüºÁÃ«ÒÑÓÃ¾¡Ò²¡£\n",me,who);
    return 1;
  }
  who->add("obstacle/rebirth",1);
  message_vision ("\n$N°Î³öÒ»¸ù¾ÈÃüºÁÃ«£¬·ğÊÖÒ»Ñï¡­¡­¡£\n",me);
  message_vision ("\n$N¶Ù¾õÌìĞüµØ×ªÇ¬À¤µ¹ÖÃ£¬É²ÄÇ¼ä½û²»×¡»ëÉí²ü¶¶£¡\n",who);
  if (who->query("death/combat_exp_loss"))
  {
    tell_object (who,"ÄãÍ»È»·¢ÏÖÄãµÄµÀĞĞÈ«²¿»Ö¸´ÁË£¡\n");
    who->add("combat_exp", (int)who->query("death/combat_exp_loss"));
  }
  if (who->query("death/skill_loss"))
  {
    tell_object (who,"ÄãÍ»È»·¢ÏÖÄãµÄÎä¹¦È«²¿»Ö¸´ÁË£¡\n");
    who->skill_death_recover();
  }
  who->delete("death");
  who->save();
  return 1;

}

void do_reward (object who)
{
  object me = this_object();
  int size1 = sizeof(obstacles);
  int size2;
  string *strs = values(obstacles);
  mapping skills = who->query_skills();
  int i;

  if (! interactive (who))
    return;

  if (who->query("obstacle/reward"))
    return;

  if (who->query_temp("no_move"))
    return;

  if (who->query("obstacle/number") < size1)
    return;

  size2 = sizeof(skills);

  message_vision ("±¦µîÀï×ÏÏ¼çÔÈÆ½ğ¹âÍòµÀ£¬$N¼ûµ½ÈçÀ´ÕæÉí»ëÉíÒ»Èí°İµ¹ÔÚµØ£¡\n",
                  who);
  message_vision ("\n$N¶Ô$nËµ£º"+RANK_D->query_respect(who)+
                  "Ò»Â·ÉÏÀú¾­ÔÖí©»¼ÄÑ£¬ÍòÀïÌöÌö¿à¾¡¹¦³ÉÒ²¡£\n",me,who);
  i = (size1+size2+2)*3;
  who->start_busy(i,i);
  who->set_temp("no_move",1);

  strs = (string *)sort_array (strs, 1);
  for (i = 0; i < size1; i++)
  {
    call_out("rewarding1",(i+1)*3,me,who,strs[i]);
  }
  call_out("rewarded1",(size1+1)*3,me,who);
  strs = keys(skills);
  for (i = 0; i < size2; i++)
  {
    call_out("rewarding2",(size1+i+2)*3,me,who,strs[i]);
  }
  call_out("rewarded2",(size1+size2+2)*3,size2,me,who);
}

void rewarding1 (object me, object who, string str)
{
  int i = 600+random(who->query("kar")*30);

  who->add("obstacle/reward",i);
  who->add("potential",i);
  message_vision ("\n$NËµµÀ£º"+str+"Ò»¹Ø£¬½±$n"+chinese_number(i)+
                  "µãÇ±ÄÜ£¡\n",me,who);
  tell_object(who,"ÄãµÄÇ±ÄÜÔö¼ÓÁË"+chinese_number(i)+"µã£¡\n");
}

void rewarded1 (object me, object who)
{
  int i = who->query("obstacle/reward");

  remove_call_out("rewarding1");
  message_vision ("\n$NÒ»µãÍ·£º¹²¼Æ"+chinese_number(i)+"µãÇ±ÄÜ£¡\n",me);
  announce (me,who->query("name")+"Î÷ÌìÈ¡¾­Àú¾­ÔÖí©£¬½±Àø"+
            chinese_number(i)+"µãÇ±ÄÜ£¡\n");
}

void rewarding2 (object me, object who, string str)
{
  int i = who->query_skill(str,1);
  string name = to_chinese(str);

  who->set_skill(str,i+1);
  message_vision ("\n$NËµµÀ£º½±ÀøÒ»¼¶"+name+"£¡\n",me,who);
  tell_object(who,"ÄãµÄ"+name+"Ôö¼ÓÁËÒ»¼¶£¡\n");
}

void rewarded2 (int size, object me, object who)
{
  remove_call_out("rewarding2");
  message_vision ("\n$NÒ»µãÍ·£º¹²¼Æ"+chinese_number(size)+"¼¶¼¼ÄÜ£¡\n",me);
  announce (me,who->query("name")+"Î÷ÌìÈ¡¾­¹¦µÂÎŞÁ¿£¬½±Àø"+
            chinese_number(size)+"¼¶¼¼ÄÜ£¡\n");
  call_out("informing",1,me,who);
}

void informing (object me, object who)
{
  who->interrupt_me();
  who->set_temp("no_move",0);
  who->save();
  me->set("my_level",LEVEL_NONE);
  me->delete_temp("invite");
  message_vision ("\n$N¶Ô$nËµ£ºÆğÉí£¬¿ÉÈ¥±¦¸óÈ¡Õæ¾­Ò»±¾¡£\n",me,who);
  message_vision ("\n$NÓÖ²¹³äµÀ£ºÈÕºóÈôÓĞ²»²â£¬¿ÉÀ´´óĞÛ±¦µîÆğËÀ»ØÉúÈı´Î¡£\n",
                  me);
}

int reward_player ()
{
  object me = this_object();
  object who = this_player();
  object *all, *list;
  int size1 = sizeof(obstacles);
  int i, j;

  if (me->query("my_level") == LEVEL_ASKED)
  {
    message_vision ("$N¶Ô$nÒ¡Í·ËµµÀ£ºÀÏ·òÕıÃ¦¡£\n",me,who);
    return 1;
  }

  if (who->query("obstacle/reward"))
  {
    message_vision ("$N¶Ô$nËµµÀ£ºÄã²»ÊÇÒÑ¾­À´¹ıÁËÂğ£¿\n",me,who);
    return 1;
  }

  if (who->query_temp("no_move"))
  {
    message_vision ("$N¶Ô$nÒ¡Ò¡Í·¡£\n",me,who);
    return 1;
  }

  if (who->query("obstacle/number") < size1)
  {
    message_vision ("$N¶Ô$nÒ¡Í·ËµµÀ£ºÄãÉĞÎ´Àú¾¡ÄÑ¹Ø¡£\n",me,who);
    return 1;
  }

  if (me->query("last_player") != who)
  {
    me->set("last_player",who);
    me->set_temp("invite","public");
    announce (me,who->query("name")+"²»Ô¶ÍòÀïÇ°À´È¡Õæ¾­£¡");
    announce (me,"ÖîÎ»ÏÉÏÍÈçÔ¸¹ÛÀñ£¬Ê¹accept rulai fo±ã¿É£¡\n");
    remove_call_out ("inviting");
    call_out ("inviting",1,me);
    return 1;
  }

  all = users();
  i = sizeof(all);
  list = all_inventory(environment(me));
  j = sizeof(filter_array(list, (:userp:))) - 1;

  if ((i/4-j) > 0)
  {
    message_vision ("$N¶Ô$nÒ¡Ò¡Í·£ºÎ÷ÓÎ¼ÇÏÖÓĞ"+chinese_number(i)+"Î»Íæ¼Ò£¬"
                    "´Ë´¦½öÓĞÊıÎ»ÏÉÏÍÔÚÑû£¬¿É·ñÔÙÑû"+chinese_number(i/4-j)+
                    "Î»ÏÉÏÍÇ°À´¹ÛÀñ£¿\n",me,who);
    if (! DEBUG)                 
      return 1;
  }
  announce (me,"Î÷ÓÎ¼ÇÎ÷ÌìÈ¡Õæ¾­¹ÛÀñ£º"+who->query("name")+"´óĞÛ±¦µî°İÀñ£¡\n");

  me->set("my_level",LEVEL_ASKED);
  do_reward (who);
  return 1;
}

void inviting (object me)
{
  int i;
  object *list;

  if (! me->query_temp("invite"))
    return;
  
  remove_call_out ("inviting");
  call_out ("inviting",4+random(4),me);

  list = users();
  i = sizeof(list);
  while  (i--)
  {
    string here, there;

    reset_eval_cost();
    if (!environment(list[i]))
      continue;
    if (environment(list[i])->query("unit")) // not a room
      continue;
    if (list[i]->is_fighting())
      continue;
    if (list[i]->is_busy())
      continue;
    if (list[i]->query_temp("no_move"))
      continue;
    if (list[i]->is_ghost()) // Checking ghost
      continue;
    if (!living(list[i]))
      continue;
    if ((string)list[i]->query_temp("accept")!=me->query("id"))
      continue;

    list[i]->set_temp("accept",0);
    here = (string)environment(me);
    there = (string)environment(list[i]);
    if (here == there)
      continue;

    message_vision("$NÈôÓĞËùË¼µØÏòÔ¶·½Éì³öÊÖ¡­¡­\n",me);
    list[i]->set_temp("accept",0);
    list[i]->set_temp("lingshan/from",there);
    message_vision("Ò»ÍÅÏéÔÆÆ®À´£¬ÔÆÖĞÉì³öÒ»Ö»¾Ş´óµÄ·ğÊÖ½«$NÇáÇáÍĞÆğ£¬ÏûÊ§ÔÚÌì¿Õ¡£\n",list[i]);
    list[i]->move(here);
    message_vision("¡­¡­$NÇáÇáÒ»·­ÕÆ£¬$nÎÈÎÈµØÌøÏÂÀ´ÂäÔÚµØÉÏ¡£\n",me,list[i]);
    break;
  }
}

int do_back(string arg)
{
  object who = this_player();
  object me = this_object();
  string here = (string)environment(me);
  string there = who->query_temp("lingshan/from");

  message_vision("$NÇëÇó$nËÍ$N»Ø·µ¡£\n",who,me);
  //if (!there)
  //  there = "/d/city/kezhan";
  there = "/d/city/kezhan";

  who->set_temp("accept",0);
  message_vision("$NµÄÊÖÕÆÇáÇáÍĞÆğ$nÏòÔ¶·½ÉìÈ¥¡­¡­\n",me,who);
  who->move(there);
  message_vision("¡­¡­ÔÆÖĞÉì³öÒ»Ö»¾Ş´óµÄ·ğÊÖÇáÇáÒ»·­£¬Ö»¼û$N´ÓÀïÃæÌø³öÀ´¡£\n",who);
  
  return 1;
}

void die()
{
  if (environment())
    message("sound", "\n\nÈçÀ´»º»ºÒ»µãÍ·£º·ğ·¨ÎŞ±ß£¡\n\n", environment());

  set("eff_kee", 10000);
  set("eff_gin", 10000);
  set("eff_sen", 10000);
  set("kee", 10000);
  set("gin", 10000);
  set("sen", 10000);
  set("force", 10000);
  set("mana", 10000);
}

void unconcious()
{
  die ();
}

ÿ