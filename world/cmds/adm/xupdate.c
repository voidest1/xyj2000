//
// xupdate.c 
// Created by vikee
// 2002.1.5
//
#include <ansi.h>
inherit F_CLEAN_UP;
int help();
int UpdateDir(object me, string file);
int update_file(object me, string file);

int main(object me, string file)
{
	seteuid(geteuid(me));
	file=resolve_path(me->query("cwd"),file);
	switch(file_size(file))
	{
		case -1:
			write("该目录(或文件)不存在。\n");
			break;
		case -2:
			write("正在重新编译文件......\n");

			if(UpdateDir(me, file)==0)
				write("重新编译中间有错误!\n");
			else
				write("重新编译成功。\n");
			break;
		default:
			update_file(me, file);
	}
	return 1;
}

int UpdateDir(object me, string file)
{
	string tmp;
	
	reset_eval_cost();

	if (file_size(file) == -2)
	{
		if(file[sizeof(file)]!='/')
				file=file+"/";

	 	foreach(tmp in get_dir(file))			
		{
			 if(!UpdateDir(me, file+tmp))					
			 return 0;
		}
	}	
	else 
	{
		file = resolve_path(me->query("cwd"), file);
		if(sscanf(file, "%*s.c")) 
			update_file(me, file);
		
	}
	return 1;
}


int update_file(object me, string file)
{
	int i;
	object obj, *inv;
	string err;
	object daemon;

	seteuid( geteuid(me) );	

	me->set("cwf", file);

	if (obj = find_object(file)) {
		if( obj==environment(me) ) {
			if( file_name(obj)==VOID_OB )
				return 0;
			inv = all_inventory(obj);
			i = sizeof(inv);
			while(i--)
				if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
				else inv[i] = 0;
		}
		destruct(obj);
	}

	if (obj) return 0;

   write("编译 " + file + "...........................");
	err = catch( call_other(file, "???") );
   	//err = call_other(file, 0);
	if (err)
		write(HIR"ERROR!\n"NOR);
	else {
		write("OK!\n");
		if( (i=sizeof(inv)) && (obj = find_object(file))) {
			while(i--)
				if( inv[i] && userp(inv[i]) ) inv[i]->move(obj, 1);
		}
	}
		
	return 1;
}


int help()
{
  write(@HELP

Xupdate 命令 

指令格式 : xupdate <文件名或目录名>
此指令可让你重新编译整个目录的文件。
用来检查这个目录的是否存在编译时段
的错误。
注意：此命令比可能回耗时较长，请不
要使用太深层次的目录。
HELP
    );
    return 1;
}
