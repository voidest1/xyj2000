
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"航空母舰<辽宁号>"NOR, ({ "carrier","aircraft carrier" }) );
        set_weight(1500000);
        set_max_encumbrance(1000000);
		set("no_get",1);
		set("value", 1000000);
        if( clonep() ) {
                object a,b,c,d,e;
                  seteuid(getuid());
                if(a=new("/obj/toy/fighter"))
                  a->move(this_object());

                  seteuid(getuid());
                if(d=new("/obj/toy/fighter"))
                  d->move(this_object());

                  seteuid(getuid());
		if(b=new("/obj/toy/fighter"))
		  b->move(this_object());

                  seteuid(getuid());
                if(e=new("/obj/toy/fighter"))
                  e->move(this_object());

                  seteuid(getuid());
		if(c=new("/obj/toy/fighter"))
		  c->move(this_object());
                set_default_object(__FILE__);
        } else {
                set("unit", "艘");
                set("long", "这是一艘巨大的航空母舰，上面停放了很多飞机！你可以尝试请他协助(xiezhu)\n");
					         
                set("value", 10000000);
        }
}

int is_container() { return 1; }

void init()
{                                             
	
	add_action("do_helpfire", "assist");
	add_action("do_helpfire", "xiezhu");

	
	//add_action("do_block","",1);

}

int do_helpfire()
{   
	object guai,me,obj,fighter;
    obj=this_object();
    me=this_player();

    if(me->query("mieyao/helpkill")==0)
		return notify_fail("本舰未接到协助你攻击的命令！\n");

	guai = find_living(me->query("mieyao/ygid"));

	if(!living(guai) || me->query("mieyao/done"))
		return notify_fail("本舰无法锁定你的目标！\n");

	if(me->query("mieyao/helpkill") > 0 && living(guai))
	{
		message_vision("一阵轰鸣，一架战斗机从航母上起飞了！\n",me);
		fighter=new("/obj/toy/fighter");
	   if(fighter->move(environment(guai)))
	   {
		tell_object(environment(guai),"一阵轰鸣，一架战斗机从云端俯冲而下！\n");
		tell_object(environment(guai),HIR"战斗机一阵机炮扫射！\n"NOR);
		guai->die();
		me->add("mieyao/helpkill",-1);
		tell_object(environment(fighter),"战斗机摇了摇翅膀，飞走了！\n");
		destruct(fighter);
		return 1;

	   }
	   else
	   {
		   destruct(fighter);
		   return notify_fail("本舰无法完成攻击任务！\n");

	   
	   }

	}

	else return notify_fail("本舰目前无法完成攻击任务！\n");

}