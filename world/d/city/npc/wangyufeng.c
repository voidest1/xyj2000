


inherit NPC;
#include <ansi.h>

void greeting(object me);

void create()
{
        set_name("王煜锋", ({"wang yufeng", "wang", "actor"}));
        set("long",@LONG
中国新生代演员，毕业于北京电影学院表演系。《民兵葛二蛋》
《追鱼传奇》《龙门镖局》中均有出色演技。现为本MUD形象代
言人。
LONG);
        set("title", HIC"新生代影视明星"NOR);
		set("nickname",HIM"本MUD形象代言人"NOR);
        set("gender", "男性");
        set("age", 30);
        set("per",40);
        set("kee", 800); 
        set("max_kee", 800);
        set("sen", 200);
        set("max_sen", 200);
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("env/wimpy", 50);
        set("chat_chance", 3);
        set("chat_msg", ({
         "王煜锋面带谄笑，点头哈腰地对大家说道：各位大名在下心仪已久，幸会！幸会！\n",
         "王煜锋环视了一下四周，抱拳诚恳地道：“请诸位多多支持！”\n",
         "王煜锋双手抱拳，作了个揖道：各位仙长请了！\n",
        }));

        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);

        setup();
        carry_object("/d/obj/cloth/choupao")->wear();
        add_money("gold", 1);
}

void init()
{
    call_out("greeting", 1, this_player());
    ::init();
}
void greeting(object who) {
  tell_object(who,"王煜锋玉树临风，风流倜傥。\n");
}

int accept_object(object who, object ob)
{
	int i;
	if (ob->query("equip_level"))
	{
		i=(int)ob->query("equip_level")+1;
		command("nod");
        command("say 感谢您参与游戏！");
		call_out("destroy", 1, ob);
		add_money("gold", i);
		command("give gold to " + who->query("id"));
		return 1;
	}
	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}