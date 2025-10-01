// cracked by vikee 2/09/2002   vikee@263.net
// mon 8/3/99

#include "/doc/help.h"

inherit F_CLEAN_UP;

string JAIL="/d/wiz/punish";
int help(object me);

int main(object me, string arg)
{
        int online;
	object who, env;

	seteuid(geteuid(me));

        if (!arg) return notify_fail("锟斤拷锟斤拷要锟斤拷谁锟斤拷锟斤拷锟斤拷危锟杰n");
	arg=replace_string(arg,"#"," ");
	arg=replace_string(arg,"."," ");

	who=find_player(arg);
	if(who) { //player online now.
	    online=1;
	    if(env=environment(who))
		message_vision("锟斤拷锟斤拷锟教斤拷锟揭恢伙拷锟斤拷纸锟饯N抓锟斤拷锟斤拷锟斤拷锟斤拷锟剿★拷\n",
			who);
	    who->move(JAIL);
	} else {
	    who=new(USER_OB);
	    who->set("id",arg);
	    if(!who->restore()) {
		write("没锟斤拷"+arg+"锟斤拷锟斤拷锟揭伙拷锟侥硷拷锟斤拷锟斤拷锟斤拷\n");
		if(who) destruct(who);
		return 1;
	    }
	    online=0;
	}
	
	who->set("startroom",JAIL);
	who->save_raw();
	log_file("to_jail","["+ctime(time())+"]"+
		this_player()->query("id")+" send "+who->query("id")+
		" to jail.\n");
	write("锟姐将"+who->query("name")+"("+arg+")锟酵斤拷锟剿硷拷锟轿★拷\n");

	if(!online) {
	    destruct(who);
	} 

	return 1;
}

int help(object me)
{
write(@HELP
指锟斤拷锟绞斤拷锟紧ojail id 

Send <id> to xyj jail.
HELP
    );
    return 1;
}