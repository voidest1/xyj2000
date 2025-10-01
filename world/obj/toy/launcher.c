
//火箭筒 by hexiu

#include <ansi.h>
#include <weapon.h>

//inherit ITEM;

inherit MACE;

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
        "east":         "东",
        "west":         "西",
        "northup":      "北边",
        "southup":      "南边",
        "eastup":       "东边",
        "westup":       "西边",
        "northdown":    "北边",
        "southdown":    "南边",
        "eastdown":     "东边",
        "westdown":     "西边",
        "northeast":    "东北",
        "northwest":    "西北",
        "southeast":    "东南",
        "southwest":    "西南",
        "up":           "上",
        "down":         "下",
        "out":          "外",
        "enter":        "里",
]);

void create()
{
        set_name(HIC"火箭筒"NOR, ({"rocket launcher","mace","launcher"}));
        set_weight(8000);
        if(clonep())
                set_default_object(__FILE__);
        else {
	set("long", "一具火箭筒，似乎可以发射(fire)。\n里面已经装了一枚火箭弹"+HIG"<非致死>。"NOR);
	set("orilong", "一具火箭筒，似乎可以发射(fire)。");

        set("unit", "具");
        set("value", 100000);
        set("no_put",1);
        set("no_sell",1);
		set("rocket_in",1);
		set("dead",0);
		

        }
        init_mace(100);
        setup();
}


int query_autoload() { return 1; }


void init()
{                                             
	
	add_action("do_fire", "fire");
	add_action("do_install","install");
	//add_action("do_turnon", "turnon");
	//add_action("do_turnoff", "turnoff");
	//add_action("do_uninstall", "uninstall");

}



int do_fire(string arg)
{
	
	
    //mixed dest;
	string dir;
		string dest;
	object env, obj,srocket;
	mapping exit;

	if ( this_object()->query("rocket_in") == 0 )
         return notify_fail("还没有装弹！\n");
	if (this_player()->query_temp("weapon") != this_object())
		return notify_fail("你没有装备这件武器！\n");


	if( !arg ) return notify_fail("你要往哪个方向开火？\n");
	env = environment(this_player());
	//if(!env) return notify_fail("你哪里也扔不出去。\n");

	if( !mapp(exit = env->query("exits")) || !exit[arg] ||  undefinedp(exit[arg]) )
		return notify_fail("这个方向发射不出去。\n");
     dest = exit[arg];

	//if (dest && objectp(dest))
	  //  obj = dest;
	//else if( !(obj = load_object(dest)) )
	  if( !(obj = load_object(dest)) )
	        return notify_fail("你要发射的区域还没有连通。\n");

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;
	srocket = new("/obj/toy/rocket");
    if (this_object()->query("dead")) srocket->set("dead",1);
	
	message_vision("$N一扣扳机，一枚火箭弹向"+dir+"飞了过去。\n",this_player());

	//this_object()->set("set_done",1);
	//srocket->set("no_get",1);
	srocket->move(obj);
	tell_object(environment(srocket),HIW"一枚火箭弹射了过来！\n"NOR);
    srocket->bomb();
	this_object()->set("rocket_in",0);
    this_object()->set("long",this_object()->query("orilong"));
	//call_out("bomb",5,1);
	return 1;


}


int do_install(string arg)
{
   object me=this_object();
   object who=this_player();
   object crocket;
   string dead_arg;
   

   if( !arg)  return notify_fail("你想装什么？\n");

   crocket=present(arg, who);
   if (! present(arg, who)) 
		return notify_fail("你身上没有这东西。\n");
   if (crocket->query("name") == me->query("name") ) 
                return notify_fail("装自己？\n");
   if (! crocket->query("is_rocket")) 
        	return notify_fail("这玩艺装不进去。\n");
   if (who->is_busy()) return notify_fail("你正忙着呢。\n");
   
   if (me->query("rocket_in"))
        	return notify_fail(me->query("name")+"已经装弹了。\n");
   
   //if (me->query("anqi/now") >0 && me->query("anqi/type") != aq->query("name") )
   //    	return notify_fail(me->query("name")+"不能装不同种类的暗器。\n");
   //else  
     
     message_vision( "$N将一"
		+crocket->query("unit")+crocket->query("name")+"装进"+me->query("name")+"里。\n",who);
     
     
	 if (crocket->query("dead")) me->set("dead",1);//dead_arg=HIR"<致死>"NOR;
	 //else {dead_arg=HIG"<非致死>"NOR;}
     
        me->set("long",me->query("orilong")+"\n里面已经装了一" 
		
		+crocket->query("unit")+crocket->query("name")+"。\n");
		
		me->set("rocket_in",1);
     //who->start_busy(3);
     destruct(crocket);
       
     return 1;
     
  }


