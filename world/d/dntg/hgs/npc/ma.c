// cracked by vikee 2/09/2002   vikee@263.net
// sgzl
#include <ansi.h>
#define NAME "ÂíÔªË§"

inherit NPC;

void create()
{
  set_name(NAME, ({"ma yuanshuai"}));
  set("male", "ÄĞĞÔ");
  set("age", 23);
  set("long", "Ò»Ö»´óÂíºï¡£\n");
  set("combat_exp", 1000000);
  set("daoxing", 1000000);

  

  set_skill("dodge", 120);
  set_skill("parry", 120);
  set_skill("dragonstep", 120);
  map_skill("dodge", "dragonstep");
  set("force", 900);
  set("max_force", 900);
  set("force_factor", 10);

  setup();
}

void init()
{
  ::init();
}

void announce_success(object who)
{
  int i;

  i = random(500);
//  message_vision (HIY NAME+"ÅÜÁË¹ıÀ´¡£\n" NOR,who);
  who->add("dntg/number",1);
  who->set("dntg/huaguo","done");
  who->add("daoxing",i+3000);
  command("chat "+who->query("name")+"Õ¶ÁË°ÔÕ¼ÎÒÃÇË®Á±¶´µÄÄ§Í·£¬Ë³Àû´³¹ı´óÄÖÌì¹¬µÚÒ»¹Ø£¡");
  command("chat ´Ó´ËÆßÊ®¶ş¶´¾«Áé½ÔÓ¦×ğ"+who->query("name")+"ÎªÍõ£¬ËæÊ±Ìıºòµ÷Ç²£¡");
  tell_object(who,"ÄãÓ®µÃÁË"+chinese_number(3)+"Äê"+chinese_number(i/4)+"Ìì"+chinese_number((i-(i/4)*4)*3)+"Ê±³½µÄµÀĞĞ£¡\n");
  message_vision (HIY NAME+"µãÍ·¹şÑüµÄ¶Ô$NËµµ½£ºÕâÊÇÎÒÃÇÖÚĞÖµÜµÄÒ»µã¶ùĞ¡ÒâË¼£¬²»³É¾´Òâ¡£\n" NOR,who);
  tell_object(who,"ÂíÔªË§¸øÄãÒ»¸öÊ¯Í·ÅÌ×Ó¡£\n");
  who->save();
}

void refuse_player(object who)
{
  string name;
  name = who->name();

  message_vision (HIY NAME+"Í»È»ÅÜÁË¹ıÀ´$NÒ¡Ò¡Í·£º"+
                  "ÎÒÃÇÕıÔÚÑ¡ºïÍõ£¬Ã»ÊÂ±ğÀ´µ·ÂÒ¡£\n" NOR,who);
  message_vision (HIY "Ëµ°Õ"+NAME+"¼±´Ò´ÒµÄÀë¿ªÁË¡£\n" NOR,who);
}

ÿÿ
