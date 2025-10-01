// cracked by vikee 2/09/2002   vikee@263.net
inherit ROOM;

void create ()
{
	set ("short", "寻真台");
	set ("long", @LONG

寻真台上乃是青红板石铺就，布局巧妙，隐有太极之意。台中放
一尺高铜炉，炉上小口中淡吐紫烟。台周有尺高护栏，皆雕龙刻
凤。远望山下，但见山若伏兽，水若游龙，宛尔有出世之意。此
处似乎可以演奏(play)。
LONG);

	set("exits", 
	([ //sizeof() == 4
		"northdown" : __DIR__"eastway1",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"npc/qingfeng" : 1,
		__DIR__"npc/hanxiangzi" : 1,
	]));


	set("outdoors", "wuzhuang");

	setup();
}

void init()
{
        add_action("do_play", "play");//add by hexiu
}

int do_play(string arg)
{	
	
	int sen_cost, kee_cost, force_cost, sk, gain;
	object me=this_player();
	object weapon = me->query_temp("weapon");
	
	sk=(int)me->query_skill("zouxiao", 1);
	


	if( !arg || (arg != "xiao"))
		return notify_fail("你要演奏什么？\n");
	if( me->is_busy() )
		return notify_fail("你忙的很，哪有功夫去演奏！\n");
	if (!weapon || weapon->query("music/type") != "xiao")
                return notify_fail("你手里的家伙吹不出调子。\n");
	if( me->is_fighting() )
		return notify_fail("现学现卖已来不及了！\n");
	if( (int)me->query_skill("literate", 1) < 100)
          return notify_fail("文盲也懂音律？\n");
	if (me->query_skill_mapped("force")!="zhenyuan-force")
                return notify_fail("只有用镇元神功才能运力吹箫。\n");
	if( (int)me->query("max_force") < 1000)
		return notify_fail("你底气不足，已经五音不全了。\n");
	
	if( sk < 199)
		return notify_fail("你吹了半天，却一直没有进展。\n");
	
	//if( sk >= 300)
	//	return notify_fail("你演奏了一会似乎有所领悟。\n");
	
	sen_cost = 80 - (int)me->query_int();
	if( (int)me->query("sen") < sen_cost )
		return notify_fail("你现在头晕脑胀，该休息休息了。\n");

	kee_cost = 80 - (int)me->query_con();
	if( (int)me->query("kee") < kee_cost )
		return notify_fail("你现在浑身无力，该休息休息了。\n");

	force_cost = 20;
	if( (int)me->query("force") < force_cost )
		return notify_fail("你现在已提不起气了，该休息休息了。\n");

	me->receive_damage("sen", sen_cost);
	me->receive_damage("kee", kee_cost);
	me->add("force", - force_cost);
	me->start_busy((int)(sk/100)+random(3));

	
    gain = sk/2+random(10);
    
	me->improve_skill("zouxiao", gain);

	write("你奏起了一曲，箫声娓娓，你对『奏箫之技』又有所了解。\n");

	tell_room( environment(me), me->name() + "奏起了一曲，箫声娓娓，瑟瑟断续。\n", ({me}));

	return 1;
}