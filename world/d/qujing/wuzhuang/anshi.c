// cracked by vikee 2/09/2002   vikee@263.net
//anshi.c
#include <room.h>
inherit ROOM;

int can_enter=1;

void create ()
{
	set ("short", "亭底暗室");
	set ("long", @LONG

这是牡丹亭底下的一间暗室。黑咕窿咚的什么也看不清。你试着
到处摸了摸(mo)。 
LONG);

	set("exits", 
	([ //sizeof() == 4
		//"southwest" : __DIR__"juyuan",
		//"north" : __DIR__"southpool",
		"up" : __DIR__"mudanting",
		//"west" : __DIR__"westway6",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"obj/huangtong-key" : 1,
	]));

	create_door("up", "桌底暗门", "down", DOOR_CLOSED);
	//set("outdoors", "wuzhuang");

	set("no_clean_up", 1);
	can_enter=1;

	setup();
}


void init()
{
	add_action("do_mo", "mo");

	if( query("started") != 1 )
	{
		set("started", 1);
		call_out("generate_key", 86400+random(100)*864);//1.5 day
	}
}

void generate_key()
{
	remove_call_out("generate_key");
	set("available", 1);
}

void reset_enter()
{
    can_enter=1;
}

int do_mo(string arg)
{
	object me, key;
	int sen;

	me = this_player();
	notify_fail("你什么也没摸着。\n");
	
	if(me->is_busy()) return 0;

	// 9/16/98 mon
	// sen cost for mo to reduce dummy flooding here.
	sen=me->query("sen");
	if(sen<110) return 0;
	sen-=100;
	me->set("sen",sen);

	// 4/2/99 mon 
	sen=(me->query("combat_exp")+me->query("daoxing"))/2;
	if(sen<10000) return 0;

	if( query("available") == 1 )
	{
		set("available", 0);
		key = new(__DIR__"obj/huangtong-key");
		key -> move(this_object());
		message_vision("只听当！地一声，一把黄铜钥匙掉在地上。\n", me);

		remove_call_out("generate_key");
		call_out("generate_key", 86400+random(100)*864);// 1.5 day
		return 1;
	}
	else
	{ 
		if( can_enter && 
			(string)me->query("zhangmen/base_name") 
			== "/d/qujing/wuzhuang/npc/zhangmen")
		{
			message_vision("$N在墙上摸索了一下，只听喀嚓！一声一道暗门翻出，把$N带到了一间秘室。\n", me);
			me->move(__DIR__"anshi-more1");

			// mon 10/19/20
			// can only enter again after a while.
			can_enter=0;
			call_out("reset_enter",1200+random(1200));
			return 1;
		}
		else return 0;
	}
}

int clean_up()
{
	return 0;
}


