// cracked by vikee 2/09/2002   vikee@263.net
//created 8-8-97 pickle
//罗春
 

inherit F_MASTER;
inherit NPC;
string try_me(object me);

void create()
{
  set_name("罗春", ({"luo chun", "luo", "chun", "luochun"}));
  set ("long", @LONG
罗春是罗府的心腹家将，办事甚是得力。传说他是罗艺的私生子，
是罗成的亲哥哥。罗春的一手霸王枪使得纯熟无比，在战场上曾经
颇立战功。
LONG);

  set("title", "罗府家将");
  set("gender", "男性");
  set("age", 40);
  set("str", 50);
  set("cor", 50);
  set("cps", 50);
  set("spi", 15);
  set("per", 25);
  set("con", 50);
  set("int", 25);
  set("kar", 10);
  set("combat_exp", 1000000);
  set_skill("force", 100);
  set_skill("lengquan-force", 100);
  set_skill("parry", 100);
  set_skill("dodge", 100);
  set_skill("yanxing-steps", 100);
  set_skill("unarmed", 100);
  set_skill("changquan", 100);
  set_skill("spear", 200);
  set_skill("bawang-qiang", 200);
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("max_sen", 600);
  set("max_kee", 1200);
  set("force", 2000);
  set("max_force", 1500);
  set("force_factor", 20);
 
  create_family("将军府", 2, "蓝");
  setup();
 
  carry_object("/d/obj/weapon/spear/tieqiang")->wield();
  carry_object("/d/obj/armor/tiejia")->wear();
}

int accept_fight(object me)
{
  command("say 在这里打架，不怕惊动了楼上的贵人？\n");
  return 0;
}

int attempt_apprentice(object me)
{
  string myname=RANK_D->query_respect(me);
  command("pat "+me->query("id"));
  command("say 很好，时下正是用人之际"+myname+"多加努力，他日必定有成。");
  command("recruit " + me->query("id") );
  return 1;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "fighter");
}