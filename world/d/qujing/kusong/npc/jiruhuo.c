// cracked by vikee 2/09/2002   vikee@263.net
inherit NPC;
inherit F_MASTER;
string expell_me(object me);

void create()
{
  set_name("急如火", ({"jiru huo","huo"}));
  set("gender", "男性");
  set("age", 10);
  set("title", "火云洞健将");
  set("long","一个贼眉鼠眼的小妖精。\n");
  set("combat_exp", 100000+random(3000));
  set("daoxing", 100000);

  set("per", 15);

  set_skill("dodge", 60);
  set_skill("parry", 60);
  set_skill("unarmed", 60);
  set_skill("force", 60);
  set_skill("spells", 60);
  set_skill("pingtian-dafa", 40);
  set_skill("huomoforce", 40);
  set_skill("moyun-shou", 40);
  set_skill("moshenbu", 40);
  set_skill("fork", 60);
  set_skill("spear", 60);
  set_skill("stick", 60);
  map_skill("force", "huomoforce");
  map_skill("spells", "pingtian-dafa");
  map_skill("unarmed", "moyun-shou");
  map_skill("dodge", "moshenbu");

  set("max_sen",800);
  set("max_kee",800);

  set("force", 400);
  set("max_force", 400);
  set("force_factor", 20);
  set("mana", 400);
  set("max_mana", 400);
  set("mana_factor", 20);

        set("inquiry", ([
                "下山": (: expell_me :),
                "leave": (: expell_me :),
]) );

  create_family("火云洞", 3, "蓝");

  setup();

  carry_object("/d/qujing/kusong/obj/tongjia")->wear();
}

void attempt_apprentice(object ob)
{       ob=this_player();

        if( (string)ob->query("family/family_name") == "火云洞") {
		command("say 大家同门中人，不敢当，不敢当！\n");
		return;
	}
                command("grin");
                command("recruit " + ob->query("id"));
                return ;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "yaomo");
                ob->set("title", "枯松涧火云洞小妖");
        }
}

string expell_me(object me)
{       me=this_player();
        if((string)me->query("family/family_name")=="火云洞") {
                me->set_temp("betray", 1);
                return ("既是要出山，却需受山规惩罚，你可愿意(agree)?");
        }
        return ("不知。");
}
void init()
{
::init();
        add_action("do_agree", "agree");
}

int do_agree(string arg)
{
        if(this_player()->query_temp("betray")) {
                message_vision("$N答道：愿意。\n\n", this_player());
                this_player()->add("betray/count", 1);
                this_player()->add("betray/huoyun", 1);
                this_player()->set("combat_exp", this_player()->query("combat_exp")*95/100);
                this_player()->delete("family");
                this_player()->delete("class");
                this_player()->set("title", "普通百姓");
                this_player()->save();
                command("say 那你去吧！\n");
                return 1;
                }
        return 0;
}