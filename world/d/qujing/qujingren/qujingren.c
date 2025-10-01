// cracked by vikee 2/09/2002   vikee@263.net
// created by ajax 05/28/1999
// 取经人

inherit NPC;
// inherit F_CLEAN_UP;

#include <ansi.h>
#include "qujingquest.c"

int ask_for_help();
int random_move_xuanzang();
int leave_this_quest_xuanzang();
int success_this_quest_xuanzang();

void create()
{

  set_name("陈玄奘", ({"chen xuanzang", "chen", "xuanzang", "san zang", "tang seng", "tang"}));
  set("gender", "男性" );
  set("age", 36);
  set("title", "三藏法师");
  set ("long", @LONG
灵通本讳号金蝉，只为无心听佛讲，转托尘凡苦受磨，降生世俗遭罗网。
投胎落地就逢凶，未出之前临恶党。父是海州陈状元，外公总管当朝长。
出身命犯落江星，顺水随波逐浪泱。海岛金山有大缘，迁安和尚将他养。
年方十八认亲娘，特赴京都求外长，总管开山调大军，洪州剿寇诛凶党。
状元光蕊脱天罗，子父相逢堪贺奖。复谒当今受主恩，凌烟阁上贤名响。
恩官不受愿为僧，洪福沙门将道访。小字江流古佛儿，法名换做陈玄奘。
LONG);

  set("class", "monk");
  set("combat_exp", 0);
  set("attitude", "peaceful");
  set_skill("fofa", 300);
  set("per", 30);
  set("max_kee", 500);
  set("kee", 500);
  set("max_sen", 500);
  set("sen", 500);

//temp flag
  set("qujing/id", "yingchou");
  set("qujing/ppl","none");


  setup();
  carry_object("/d/obj/cloth/hufa-jiasha")->wear();


  set("inquiry", ([
     "name"     :   "贫僧东土大唐人士，奉我皇太宗旨意前去西天取经。",
     "qujing"   :   (: ask_for_help() :),
     "取经"     :   (: ask_for_help() :),
     ]) );

  set("chat_msg", ({
      (: random_move :),
        }) );
  set("chat_chance", 20);

}

// 开始过关
int ask_for_help()
{
  object me = this_object();
  object who = this_player();
  int daoxing_needed,time_needed;

  sscanf(obstacles[me->query("qujing/id")][1],"%d",daoxing_needed);
  daoxing_needed=daoxing_needed*1000;
  sscanf(obstacles[me->query("qujing/id")][5],"%d",time_needed);
  time_needed=time_needed*60;

  if (who->query("class") == "yaomo" )
    {
    message_vision("$N对$n道：施主满脸妖气，不知来此是何居心，"
         +"苦海无边，回头是岸，我劝施主还是好自为之吧。\n", me,who);
    return 1;
    }

  if (who->query("daoxing") < daoxing_needed )
    {
    message_vision("$N对$n说到：多谢施主的好意，只是这路途艰险，"
         +"妖魔众多，恐怕贫僧连累了施主。\n", me,who);
    return 1;
    }

  if (me->query("qujing/ppl") == who->query("id") )
    {
    message_vision("$N对$n说到：事不疑迟，咱们还是赶紧赶路吧。\n", me,who);
    return 1;
    }

  if (me->query("qujing/ppl") != "none" )
    {
    message_vision("$N对$n一抱拳：多谢"
         +RANK_D->query_respect(who)+"的好意，已有人帮助贫僧了。\n", me,who);
    return 1;
    }

  if (me->query("qujing/id"))
    {
    message_vision("$N向$n一拱手：贫僧"+obstacles[me->query("qujing/id")][3]
       +RANK_D->query_respect(who)+"能否助贫僧一臂之力？\n", me,who);
    me->command("follow "+who->query("id"));
    me->set("chat_chance",0);
    me->set("qujing/ppl",who->query("id"));
    remove_call_out("random_move_xuanzang");
    remove_call_out("leave_this_quest_xuanzang");  
    call_out("success_this_quest_xuanzang", 1);  
    call_out("leave_this_quest_xuanzang", time_needed);  
    return 1;
    }
}

// 每隔六分终如果没人过关，auto move to a new quest place
int random_move_xuanzang()
{
  int i;
  string *quest_id = keys(obstacles);
  object me = this_object();
  
  i=random(sizeof(quest_id));
  me->move(obstacles[quest_id[i]][2]);
  me->set("qujing/id",quest_id[i]);
  me->set("qujing/ppl","none");
  set("chat_chance", 20);
  remove_call_out("random_move_xuanzang");
  call_out("random_move_xuanzang", 300);  
  return 1;
}


int leave_this_quest_xuanzang()
{
  object me = this_object();
  message_vision("$N长叹一声：西行之路竟如此艰辛。\n", me);
// here need clear ppl's mark and give punishment 
  message_vision("$N黯然的离开了。\n", me);
  call_out("random_move_xuanzang", 1);  
  return 1;  
}

int success_this_quest_xuanzang()
{
  object me = this_object();
  object who;
  int reward_daoxing;

  sscanf(obstacles[me->query("qujing/id")][6],"%d",reward_daoxing);
  who=find_player(me->query("qujing/ppl"));
  if (who)
    {
    me->command("chat "+who->query("name")+obstacles[me->query("qujing/id")][4]
       +who->query("name")+"闯过西行又一关！");
// here need clear ppl's mark and give reward 
    message_vision("$N向$n一拱手：多谢"+RANK_D->query_respect(who)+
         "相助，咱们后会有期！\n", me,who);
    message_vision("$N继续向西赶路去了。\n", me);
    call_out("random_move_xuanzang", 1);  
    }
  return 1;  
}


void unconcious()
{
  die ();
}

void die()
{
  object me = this_object();
  message_vision("$N长叹一声：我不入地狱，谁入地狱，"
      +"只是取经未成，辜负了我王太宗的一片诚心。\n", me);
  message_vision("$N死了。\n", me);
// 出现唐僧肉
  set("eff_kee", 500);
  set("eff_sen", 500);
  set("kee", 500);
  set("sen", 500);
  me->move(__DIR__"shengsilunlui");
  call_out("random_move_xuanzang", 1800);  
}

