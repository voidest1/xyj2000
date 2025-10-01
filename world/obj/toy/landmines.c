#include <ansi.h>
//inherit /obj/toy/bomb.c
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
        set_name(HIG"地雷<非致死>"NOR, ({"land mines", "landmines","mines"}));
        set_weight(10000);
        if(clonep())
                set_default_object(__FILE__);
        else {
	set("long", "一颗沉甸甸的地雷，上面有个开关，似乎可以设置在某地(sethere)。\n
还有一个开关可以设定档位。(turnoff:"HIG"非致死"NOR"/turnon:"HIR"致死"NOR")\n");
        set("unit", "颗");
        set("value", 0);
        set("no_put",1);
        set("no_sell",1);
		set("dead",0);
		set("sethere",0);
		set("set_down",0);
		

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
tell_object(env,"一声巨响，地雷爆炸了！\n");

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
			if(userp(ob[i])) ob[i]->set_temp("death_msg", "被地雷炸死了。\n");
			ob[i]->die();
	  
	  }

        }

 destruct(this_object());
 return 1;
}



void init( )
{       
	

	
    object ob=this_player();
	//::init();
//	if ( living(ob) && !wizardp(ob) && query("setb")==1 ) bomb(); 
	if ( living(ob) && query("sethere")==1 )  bomb(); 
	
	 add_action("do_sethere", "sethere");
   // add_action("do_block","",1);
	add_action("do_turnon", "turnon");
	add_action("do_turnoff", "turnoff");         
		// remove_call_out("greeting");
	                //call_out("greeting", 1, ob);
	
}


int do_turnon()
{   if (this_object()->query("set_done") == 1 )
         return notify_fail("还不快跑！！！\n");
	if (!wizardp(this_player()) )
         return notify_fail("致死挡只有巫师可以设置！\n");
	message_vision(HIW"$N把地雷的档位拨到"HIR"致死"HIW"上。\n"NOR,this_player());
        this_object()->set("no_give",1);
	this_object()->set("dead",1);
	this_object()->set("name",HIR"地雷<致死>"NOR);
	return 1;
}

int do_turnoff()
{
	if (this_object()->query("set_done") == 1 )
         return notify_fail("还不快跑！！！\n");
	message_vision(HIW"$N把地雷的档位拨到"HIG"非致死"HIW"上。\n"NOR,this_player());
	this_object()->set("dead",0);
	this_object()->set("name",HIG"地雷<非致死>"NOR);
	return 1;
}

int do_sethere()
{
	if (this_object()->query("set_done") == 1 )
         return notify_fail("还不快跑！！！\n");
	if (this_object()->move(environment( this_player() )))
	{	
		this_object()->set("no_get",1);
		this_object()->set("set_done",1);

	tell_object(environment(this_player()),HIW"地雷放置完毕，请在十秒内离开！\n"NOR);
	call_out("set_doing",10,1);
	}
	return 1;
}


void set_doing()
{
	if(this_object())  this_object()->set("sethere",1);
	return;
	
}



/*
int do_block(string arg)
{
  object me=this_object();
    object who=this_player();
    string verb=query_verb();
    int t;
    
    if(wizardp(who)) return 0;
   // if(me->is_fighting()) return 0;
if (me->query("setb")==1)
{
    if(verb!="go" &&
	    verb!="fly" &&
	    !(environment() && environment()->query("exits/" + verb)))
	return 0;

    if(who->query_temp("mieyao/allow_to_go")) {
	who->delete_temp("mieyao/allow_to_go");
	who->delete_temp("mieyao/leave_time");
	return 0;
    }
    t=who->query_temp("mieyao/leave_time");
    if(t>0 && time()>t) {
	who->delete_temp("mieyao/leave_time");
	//message_vision("$n乘$N一个不注意，急忙溜了过去。\n",me,who);
	return 0;
    }

    if(t==0) {
        t=time()+30+random(90);
        who->set_temp("mieyao/leave_time",t);
	//message_vision("$N猛地跳过来拦在$n面前，高声叫道：\n"+
	//	"          此山是我开，此树是我栽！\n"+
	//	"          要打此路过，留下买路财！\n\n",me,who);
    } 
    
    tell_object(who,me->name()+"被你踩上了！\n");

    return 1;}
	
}
*/
