// cracked by vikee 2/09/2002   vikee@263.net
inherit NPC;
 
void do_drink();
 
void create()
{
        seteuid(getuid());
        set_name("���", ({"li bai", "li"}));
        set("long", "��ʫ����ף����Ʈ�ݣ�����ͨ��\n");
        set("gender","����");
	set("title", "ʫ��");
	set("class", "scholar");
        set("age",37);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
        set("combat_exp",100000);
        set("attitude","heroism");
        set("chat_chance",20);
        set("chat_msg", ({
        "��׵�����������Σ¥�߰ٳߣ��ֿ�ժ�ǳ���\n",
        "��׵����������������ǧ�꣬�����غ�ͨ���̡�\n",
        "��׹ĸ����裺��������ȥ��������������\n",

"��׻��ڶ��裺�Կ��Ϻ�ӧ���⹳˪ѩ���������հ�������������ǡ�\n",
        (: do_drink :),
        "��׵�������������ߣ�����֮���á������ߣ��ٴ�֮���͡�\n",

"��׻��ڶ��裺����л���죬���������ݡ���ڼ����գ��������켦��\n",
        "����������·�ԶӰ�̿վ���Ψ�������������\n",
        "����������������֮�ѣ����������죬������������ൡ�\n",
        (: do_drink :),
        "��׵������������������ᣬ���������ơ�\n",
        "�����̬��¶��������������������ñ���谮�����ˡ�\n",
        "��׳���������������������գ��������ڡ�\n",
	(: random_move :)
        }));

        set("chat_chance", 10);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("unarmed", 80);
        set_skill("sword", 120);
        set_skill("literate", 120);
	set("max_force", 200);
	set("force", 200);
	set("force_factor", 10);
        set("max_kee", 700);
        set("max_gin", 400);
        set("max_sen", 500);

        setup();
        carry_object("/obj/cloth")->wear();
        carry_object("/d/obj/weapon/sword/changjian")->wield();
	carry_object("/d/obj/book/poem");
        add_money("silver", 40);
}
 
void do_drink()
{
    object *list, ob;
    int i, can_drink;
    if ((int)this_object()->query("water") >= 380) return;
    list = all_inventory(this_object());
    i = sizeof(list);
    can_drink = 0;
    while (i--) {
        if ((string)list[i]->query("liquid/type") == "alcohol") {
            ob = list[i];
            can_drink = 1;
        }
    }
    if (can_drink) {
        command("drink "+(string)ob->query("id"));
        if ((int)ob->query("liquid/remaining") == 0)
            command("drop "+(string)ob->query("id"));
    }
    else {
        command("sigh");
        command("say �ƣ��������Ҿƣ�����");
    }
    return;
}

int accept_object(object who, object ob)
{	object m;
	m=new("/d/obj/book/jianpu.c");
    if ((string)ob->query("liquid/type")=="alcohol")
    {
        if ((int)ob->query("liquid/remaining") == 0)
        {
            command("shake");
            command("say �յ��Ҳ�Ҫ������");
            return notify_fail("������ײ��������õģ���Ҫ��ƿ�ӡ�\n");
        }
        else
                if ( (string)ob->name()=="ţƤ�ƴ�" )
                {
                        command ("frown");
                        command ("say ��ƻ����������Լ��Ȱɡ�");
                        return
notify_fail("������׿�����������ľơ�\n");
                }
                else
                {
                        command("smile");
                        command("say ��л!");
			if ((int)who->query_temp("mark/���") < 1){
			who->set_temp("mark/���", 1 ); 
			}
                        if(present("jian pu", this_object())) {
			return 0;
			}
                        who->add_temp("mark/���", 1 );
                        call_out("destroy", 1, ob);
                if ((int)who->query_temp("mark/���") >= 5+random(5))
                        {
command ( "whisper " + who->query("id") + 
" �ҿ���Ҳ��λ����ϰ����ˣ�Ҳ��������Ե���Ȿ���׾��͸�����ȥ�ж��ɡ�\n");
				m->move(who);
                                who->set_temp("mark/���", 0 );
				return 1;
                        }
                        return 1;
                }
        }
    }

void destroy(object ob)
{
        destruct(ob);
        return;
}