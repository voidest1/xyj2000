// cracked by vikee 2/09/2002   vikee@263.net
inherit F_VENDOR_SALE;

int base_price=50000;

int ask_party();
int ask_money();
void create()
{
	reload("xifuhui");
        set_name("�Ϻ���", ({"xifuhui boss","boss" }));
	set("title", "ϲ�����ϰ���");
	
        set("age", 32);
        set("gender", "Ů��");
        set("attitude", "friendly");

        set("combat_exp", 50000);
  set("daoxing", 50000);


        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
	set("per", 20);

set("inquiry", ([
"name": "���±���������ϰ塣\n",
"here": "������ϲ���ᣬ���д��˼ҽ�鶼Ҫ�������ϲ������\n",
"��" : (: ask_party :),
"ϲ��" : (: ask_party :),
"ϯ" : (: ask_party :),
"��ϯ" : (: ask_party :),
"party" : (: ask_party :),
"money": (: ask_money :),
]) );
        setup();
        carry_object("/d/obj/cloth/pink_cloth")->wear();
}

void init()
{
    ::init();
	add_action("do_serve", "serve");
	add_action("do_finish", "finish");
	add_action("do_start", "start");
  	add_action("do_fight", "fight");
  	add_action("do_kill", "kill");
  	add_action("do_steal", "steal");
  	add_action("do_cast", "cast");
  	add_action("do_exert", "exert");
  	add_action("do_perform", "perform");
  	add_action("do_bian", "bian");
	add_action("do_fight", "fight");

}
int ask_party()
{	object me, who, wife;
	me=this_object();
	who=this_player();
//	if( !who->query("married") ) {
//		message_vision("$N����$n��Ц�������㻹û����أ���ʲôϲ�磡\n", me, who);
//		return 1;
//	}
//	if( who->query("married_party") ) {
//		message_vision("$N����$n���ɵ��ʵ����㲻���Ѿ�����ϲ������\n", me, who);
//		return 1;
//	}
	if( who->query_temp("host_of_party") ) {
		message_vision("$N��$n˵���ⲻ��������ϲ������\n", me, who);
		return 1;
	}
//	if( (string)who->query("gender")=="Ů��" ) {
//		message_vision("$N������ü����$n˵�������ǽ�����ɷ���������°ɣ�\n", me,who);
//		return 1;
//	}
//	if( !objectp(wife=present(who->query("couple/id"), environment(who))) ) {
//		message_vision("$N��$n˵�������Ӷ�û������ϲ����ô����\n", me, who);
//		return 1;
//	}
	if( me->query_temp("ready_to_party") ) {
		message_vision("$N��$n������˼��˵������������һϯ�أ�Ҫ�������������ɣ�\n", me, who);
		return 1;
	}
	if( (string)environment(me)->query("short")!="ϲ����" ) {
		message_vision("$N��$nΪ�ѵ�˵����������Ҳû׼��������������������\n", me, who);
		return 1;
	}
	if( who->query_temp("ready_to_pay") ) {
		message_vision("$N��$n���η���˵��������ô�ʸ�û�꣡\n", me, who);
		return 1;
	}
	if( !who->query_temp("party_paid") ) {
		message_vision("$N��$n˵����һ��ϲ���𣬿�Ҫ����"+
			price_string(base_price*query_price()/10)+
			"�أ�\n", me, who);
		who->set_temp("ready_to_pay", 1);
		return 1;
	}
}
int accept_object(object who, object ob)
{
	object m;
	int value;
	int price;

	value=ob->value();

	if( !who->query_temp("ready_to_pay") )
		return notify_fail(name()+"���ɵĿ����㣬��֪�������ʲô��\n");

	if( !value )
		return notify_fail(name()+"��ֵĿ�����˵���������ʲô��\n");

	price=base_price*query_price()/10;

	if( value < price )
		return notify_fail(name()+"˵����Щ�Ĺ�ѽ��Ҫ"+
			price_string(price)+"���У�\n");
	if(!take_money(value, base_price))
	    return 0;
	this_object()->save();
	who->set_temp("host_of_party", 1);
	who->delete_temp("ready_to_pay");
	call_out("destroy", 1, ob);

	call_out("count_money", 2, who);
	call_out("start_party", 5, who);
	return 1;
}

int ask_money()
{
	object who=this_player();
	int i;
	i=(int)this_object()->query("money")+160;
	if( who->query("id")!="bula"){ 
		command("dunno");
		return 1;
	}
	command("whisper bula ��������ⲻ���������ڹ�׬��"
+chinese_number(i)+"�������ˡ�\n");
	return 1;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}
void count_money(object who)
{
	message_vision("\n$N��$n����Ǯ��ϸ�������һ�顣\n\n", this_object(), who);
	message_vision("$Nʹ���˵����ϯ��\n", this_object() );

}

void start_party(object who)
{
	object me=this_object();
	command("chat* "+name()+
	       "����λ��ү̫̫��үС�㣬����" + who->query("name") +  
"��ϲ����󿪾�ϯ����ӭ��λǰ��������");
	command("say ��Ҫ��ʼ(start)���ұ㿪ϯ����Ҫ�ϲ�(serve)���Ҿ��ϲˣ������Ա��ˣ������ˣ��۾ͽ���(finish)��");
	me->set_temp("ready_to_party", 1);
}
int do_start()
{	
	object who = this_player();
        object me = this_object();
	int i;
	object *list;
	object girla,girlb,girlc,girld,cup;
	if( !who->query_temp("host_of_party") )
		return notify_fail(name()+"����˵�����ֲ������ɹ٣�\n");
	if( !me->query_temp("ready_to_party") )
		return notify_fail(name()+"����˵����ʼʲôѽ��������û�˽�飡\n");
	if( me->query_temp("party_start_already") )
		return notify_fail(name()+"�����Ķ���˵���ⲻ���Ѿ���ʼ���\n");

	message_vision("$N������$n˵���ϰ壬��ϯ��\n\n", who, me);
	message_vision("$N�������ţ�������ϯ����ඡ���\n\n", me);
	me->set_temp("party_start_already", 1);
	me->delete_temp("ready_to_party");
	tell_room( environment(who), "�Ա��ĸ������ִ����Ĵ����˻�������š�\n");	

	// mon
	environment(me)->set("resource/nuerhong",1);

	list = all_inventory(environment(me));
	i = sizeof(list);
	while (i--)
	{
	  	object ob= list[i];
	 	if( cup=new("/d/obj/food/dishes/cup"))
	  	cup->move(ob);
	}
	seteuid(getuid());
	if(girla=new("/d/city/npc/girla"))	
 	girla->move(environment(me));

        seteuid(getuid());
        if(girlb=new("/d/city/npc/girlb"))
        girlb->move(environment(me));

        seteuid(getuid());
        if(girlc=new("/d/city/npc/girlc"))
        girlc->move(environment(me));

        seteuid(getuid());
        if(girld=new("/d/city/npc/girld"))
        girld->move(environment(me));

	tell_room(environment(who), "�����߳�����Ư����С���\n");
	tell_room(environment(who), "��õ���һ�������յ��\n");
	call_out("finish_party", 500, who);
	return 1;
}
int do_serve()
{
	object me=this_object();
	object who=this_player();
	object food;
	if( !who->query_temp("host_of_party") )
		return notify_fail(name()+"�����µ������˻�û˵�������¸�ʲô����\n");
	if( !me->query_temp("party_start_already") )
		return notify_fail(name()+"����˵���㻹û������ʼ(start)����ô�ϲ��أ�\n");
	if ( (present("food 2", environment(me))) )
		return notify_fail(name()+"����˵�������ԣ�������Ȼ������ϲˡ�\n");

	message_vision("$N���������ţ��ϲˣ��ϲˣ�\n", who);

	tell_room(environment(me), "�������ܳ������С��ƣ��ֽ������Ľ����ϵ�ʣ�˷�������ȥ��\n");
	tell_room(environment(me), "С����ִ����ó�����������һ���µľ�ϯ��\n");
        if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
	if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
	if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
	if(food=new("/d/obj/food/dishes/food"))
        food->move(environment(me));
	return 1;
}
int do_finish()
{
	object me=this_object();
	object who=this_player();

	if( !who->query_temp("host_of_party") )
		return notify_fail(name()+"������һ�ۣ�����˵����\n");

	if( !me->query_temp("party_start_already") )
		return notify_fail(name()+"������һ�ۣ������Ѿ���������\n");
	message_vision("$N��$n˵�����Ա����㣬��л�ϰ��д���\n", who, me);
	remove_call_out("finish_party");
	call_out("finish_party", 3, who);
	return 1;
}
void finish_party(object who)
{
	object me=this_object();
        int i;
        object *list;

	message_vision("$N����˵������ϯ�ʹ˽�������л��ҹ��٣�\n", me);

	// mon
	environment(me)->set("resource/nuerhong",0);

	command("gongxi " + who->query("id"));

	me->delete_temp("party_start_already");
	who->delete_temp("host_of_party");
//	who->set_temp("married_party", 1);
	list=all_inventory(environment(me));
	i=sizeof(list);
	while (i--)
	{
		if(list[i]->query("id") != "ban niang")
			continue;
		else
			destruct (list[i]);
	}
}
int do_fight(string arg)
{
        object who = this_player();
        object me = this_object();
        message_vision("$N��ɫ����ԣ�������ɱ����\n", who);
        message_vision("$N��$nֱҡͷ�����ϲ�����Ӷ�ʲô��ǹ����\n", me, who);
        return 1;
}

int do_kill(string arg)
{
  	object who = this_player();
 	object me = this_object();

	if(!arg || present(arg,environment(me))!=me) return 0;

	message_vision("$N��ɫ����ԣ�������ɱ����\n", who);
	message_vision("$N��$nֱҡͷ�����ϲ�����Ӷ�ʲô��ǹ����\n", me, who);
	return 1;
}
int do_cast(string arg)
{
        object who = this_player();
        object me = this_object(); 
	message_vision("$N�ſ��죬���ɰɵ����˼������\n", who);
        message_vision ("$N��$nֱҡͷ�����ϲ�����ӣ������������䰡��\n", me, who);
        return 1;
}        
int do_exert(string arg)
{               
        object who = this_player();
        object me = this_object();
	message_vision("$N���������һ������\n",who);
        message_vision("$N��$n������ͷ��˵���ճԹ�������Ҫ�����ڹ���\n", me, who);
        return 1;
}
int do_perform(string arg)
{
        object who = this_player();
        object me = this_object();
	message_vision("$N��ɫ����ԣ�������ɱ����\n", who);
        message_vision ("$N��$nֱҡͷ�����ϲ�����Ӷ�ʲô��ǹ����\n", me, who);  
        return 1;
}        
int do_steal(string arg)
{       
        object who = this_player();
        object me = this_object();
	message_vision("$N����֣���Ҫ͵��ʲô��\n", who);
        message_vision ("$N��$n��������������컯��ʩ�����ԣ�\n",me,who);
  	return 1;
}

int do_bian(string arg)
{
  	object who = this_player();
  	object me = this_object();
	message_vision("$N�������������ʲô������\n",who);
	message_vision("$N��$n˵������ϲ�磬��������仯��\n",me,who);
        return 1;
}

�