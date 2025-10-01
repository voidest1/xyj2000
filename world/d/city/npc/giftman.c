// zaoshen.c

//inherit F_VENDOR_SALE;

#include <ansi.h>

inherit NPC_SAVE;

void create()
{
		reload(query_save_file());
        set_name("灶王爷", ({"zao wangye","wangye"}));
        set("title", "南城客栈");
        set("gender", "男性" );
        set("age", 16);
        set("long", "一个被供养得胖胖的灶王爷，正冲着你笑．\n");
        set("combat_exp", 2000);
        set("attitude", "friendly");
        setup();
}
void init()
{
	//::init();
	add_action("do_yao","yao");
}

int do_yao(string arg)
{
	object m,mm,me;
	message_vision("$N嬉皮笑脸地向灶王爷问道:我是新来的，有没有见面礼呀?\n", this_player());
	me=this_player();
	if ( me->query("wizgift/newbiegift") )
	{
		return notify_fail("灶王爷一瞪眼：想蒙我？\n"); 
	}
//	if ( me->query("combat_exp") < 5000 )
//	 return notify_fail("灶王爷说道: 小家伙练点功夫再来罢!\n");
//
	m=new("/d/city/npc/obj_ex/giftbox");
//        mm=new("/obj/money/thousand-cash");
	m->move(this_player());
//        mm->move(this_player());
	me->set("wizgift/newbiegift",1);
	log_file("static/NEWBIEGIFT","["+ctime(time())+"] "+sprintf("%s(%s)从灶王爷处得到了%s(%s)\n",
		this_player()->query("name"),this_player()->query("id"),
		m->query("name"),m->query("id")));
	message_vision("灶王爷给$N一个礼品盒.\n", this_player());
//        message_vision("灶王爷给$N一张一千两的银票\n",this_player()); 
	message_vision("灶王爷对$N笑道：好好练。\n", this_player());
	return 1;
}

int accept_object(object who, object item)
{
	string code;
	string *base_char = ({
			 "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"
			,"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
			,"0","1","2","3","4","5","6","7","8","9","0","1","2","3","4","5","6","7","8","9"
		});
	int cnt_char, i, len_code;
	object npc = find_object("/d/city/npc/giftman");
	object me = this_player();
	if(base_name(item) == "/d/obj/drug/renshen-guo")
	{
		command("say 这位" + RANK_D->query_respect(me) + "果然是位有心人！");
		command("say 别的我帮不上，但给个邀请码是没问题的。");
		printf( "你可以用 " + HIC +  "yqm" + NOR + " 查看已获得邀请码列表。\n");

		cnt_char = sizeof(base_char);
		code = "";

		for(len_code=8; ; len_code++)
		{
			for(i=0; i<len_code; i++)
			{
				code = code + base_char[random(cnt_char)];
			}

			if(!this_object()->query("yqm/#"+code))
				break;
		}

		this_object()->set("yqm/"+me->query("id")+"/"+code, "");
		this_object()->set("yqm/#"+code, me->query("id"));
		this_object()->save();
		return 1;
	}
	return 0;
}