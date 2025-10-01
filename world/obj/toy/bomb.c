
//定时炸弹 by hexiu

#include <ansi.h>
inherit ITEM;

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
        set_name(HIG"定时炸弹<非致死>"NOR, ({"time bomb", "bomb"}));
        set_weight(10000);
        if(clonep())
                set_default_object(__FILE__);
        else {
	set("long", "一颗炸弹，上面有个定时器，似乎可以定时起爆(settime)。\n
还有一个开关可以设定档位。(turnoff:"HIG"非致死"NOR"/turnon:"HIR"致死"NOR")\n");
        set("unit", "颗");
        set("value", 0);
        set("no_put",1);
        set("no_sell",1);
		set("dead",0);
		set("set_done",0);
		

        }

        setup();
}



void bomb()
{
int damage,i,n,j,success;
string msg;
object *ob;
object env,obj;
mapping exit;
   string *dirs, target_dir, dest;



 env=environment( this_object() );
 ob = all_inventory( env );

if(!this_object()) return ;
tell_object(env,"一声巨响，炸弹爆炸了！\n");

if (this_object()->query("dead")==0)  
{
      for(i=0; i<sizeof(ob); i++) 
		{
			if( !living(ob[i]) || ob[i]==this_object() || wizardp(ob[i])) continue;
	

                damage = 1;
                
                        ob[i]->receive_damage("sen", damage, this_object());
                        
                        tell_object(ob[i], "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n");
						COMBAT_D->report_sen_status(ob[i]);
			  
						msg = HIC "巨大的冲击波把"+ob[i]->name()+"炸的" NOR;
                        exit=env->query("exits");


 if( mapp(exit) && sizeof(env->query("exits")) != 0) {
				dirs=keys(exit);
				n=sizeof(exit);
				j=random(n);
				dest=exit[dirs[j]];
				if(!undefinedp(default_dirs[dirs[j]]))
					target_dir=default_dirs[dirs[j]];
				else
					target_dir=dirs[j]; 

				if( obj=load_object(dest)) {
					success=1;
					msg+= HIC "向" +target_dir+ NOR;
				}
msg += HIC "飞了出去！\n\n" NOR;
			}

  
  if( success == 1){
    tell_object(env,msg);

				if( ob[i]->move(obj) ) {

					tell_object(environment(ob[i]),HIR"\n只见"+ob[i]->name()+"象捆稻草般的飞了过来！\n" NOR);}

										}

					}

}
	  else{
		  for(i=0; i<sizeof(ob); i++) 
		{
			if( !living(ob[i]) || ob[i]==this_object() || wizardp(ob[i])) continue;
			if(userp(ob[i])) ob[i]->set_temp("death_msg", "被炸弹炸死了。\n");
			ob[i]->die();
	  
	  }

        }

 destruct(this_object());
 return ;
}



void init()
{                                             
	
	add_action("do_settime", "settime");
	add_action("do_turnon", "turnon");
	add_action("do_turnoff", "turnoff");
	//add_action("do_block","",1);

}



int do_settime(string arg)
{
	int timea,k,d;
	if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");
	if( !arg
        ||      !sscanf(arg, "%d", timea) )
                return notify_fail("你要定时多少？\n");

	if( timea < 5)
		return notify_fail("请给自己留下足够跑路的时间！\n");
	if( timea > 60)
		return notify_fail("炸弹定不了那么长时间！\n");

	if (this_object()->move(environment( this_player() )))
	{	
		this_object()->set("no_get",1);
		this_object()->set("set_done",1);
	    tell_object(environment(this_player()),HIW"某人丢下一个滴滴响的东西！\n"NOR);

        for(k=timea-1;k>=1;k--)
		{
	    d=timea-k;
		call_out("show_time",k,d);
		}
		call_out("bomb",timea,1);
		return 1;
	}
//	destruct(this_object());}
}

int do_turnon()
{   if (!wizardp(this_player()) )
         return notify_fail("致死挡只有巫师可以设置！\n");
    if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");

	message_vision(HIW"$N把炸弹的档位拨到"HIR"致死"HIW"上。\n"NOR,this_player());
        this_object()->set("no_give",1);
	this_object()->set("dead",1);
	this_object()->set("name",HIR"定时炸弹<致死>"NOR);
	return 1;
}

int do_turnoff()
{
	if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");
	message_vision(HIW"$N把炸弹的档位拨到"HIG"非致死"HIW"上。\n"NOR,this_player());
	this_object()->set("dead",0);
	this_object()->set("name",HIG"定时炸弹<非致死>"NOR);
	return 1;
}



void show_time(int d)
{
	if(!this_object()) return ;
	if( d<=3 ) 
	{
		tell_object(environment( this_object() ),HIR"\n"+chinese_number(d)+"\n滴滴滴！！！\n"NOR);
		return;}
	else
	{

    tell_object(environment( this_object() ),HIY"\n"+chinese_number(d)+"\n"NOR);
	return;}
}







