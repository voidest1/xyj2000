
//手榴弹 by hexiu

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
        set_name(HIG"手榴弹<非致死>"NOR, ({"hand grenade", "grenade","shou liudan","liudan"}));
        set_weight(5000);
        if(clonep())
                set_default_object(__FILE__);
        else {
	set("long", "一颗手榴弹，似乎可以定时扔出去(pull)。\n
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



int bomb()
{
int damage,i,n,j,success;
string msg;
object *ob;
object env,obj;
mapping exit;
   string *dirs, target_dir, dest;



 env=environment( this_object() );
 ob = all_inventory( env );

if(!this_object()) return 1;


tell_object(env,"一声巨响，手榴弹爆炸了！\n");

if (this_object()->query("dead")==0)  
{
      for(i=0; i<sizeof(ob); i++) 
		{
			if( !living(ob[i]) || ob[i]==this_object() || wizardp(ob[i])) continue;
	

                damage = 1;
                
                        ob[i]->receive_damage("sen", damage,this_object());
                        
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
			if(userp(ob[i])) ob[i]->set_temp("death_msg", "被手榴弹炸死了。\n");
			ob[i]->die();
	  
	  }

        }

 destruct(this_object());
 return 1;
}



void init()
{                                             
	
	add_action("do_pull", "pull");
	add_action("do_turnon", "turnon");
	add_action("do_turnoff", "turnoff");
	//add_action("do_block","",1);

}



int do_pull(string arg)
{
	
	
    //mixed dest;
	string dir;
		string dest;
	object env, obj;
	mapping exit;

	if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");

	if( !arg ) return notify_fail("你要往哪个方向扔？\n");
	env = environment(this_player());
	//if(!env) return notify_fail("你哪里也扔不出去。\n");

	if( !mapp(exit = env->query("exits")) || !exit[arg] ||  undefinedp(exit[arg]) )
		return notify_fail("这个方向扔不出去。\n");
     dest = exit[arg];

	//if (dest && objectp(dest))
	  //  obj = dest;
	//else if( !(obj = load_object(dest)) )
	  if( !(obj = load_object(dest)) )
	        return notify_fail("你要扔的区域还没有连通。\n");

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;

	message_vision("$N掏出一颗手榴弹拉了引信向"+dir+"扔了过去。\n",this_player());
	this_object()->set("set_done",1);
	this_object()->set("no_get",1);
	this_object()->move(obj);
	tell_object(environment(this_object()),HIW"一颗冒烟的东西被扔了过来！\n"NOR);
	call_out("bomb",5,1);
	return 1;


}

int do_turnon()
{   if (!wizardp(this_player()) )
         return notify_fail("致死挡只有巫师可以设置！\n");
    if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");

	message_vision(HIW"$N把手榴弹的档位拨到"HIR"致死"HIW"上。\n"NOR,this_player());
        this_object()->set("no_give",1);
	this_object()->set("dead",1);
	this_object()->set("name",HIR"手榴弹<致死>"NOR);
	return 1;
}

int do_turnoff()
{
	if ( this_object()->query("set_done")==1 )
         return notify_fail("还不快跑！！！\n");
	message_vision(HIW"$N把手榴弹的档位拨到"HIG"非致死"HIW"上。\n"NOR,this_player());
	this_object()->set("dead",0);
	this_object()->set("name",HIG"手榴弹<非致死>"NOR);
	return 1;
}


/*
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

*/