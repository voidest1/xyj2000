
#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	object* npc_list = children("/d/city/npc/giftman");
	object kz = load_object("/d/city/kezhan");
	object npc;
	string key, *arrKey, code_user;
	mapping mapYQM;

	for(int i=0; i<sizeof(npc_list); i++)
	{
		if(kz == environment(npc_list[i]))
		{
			npc = npc_list[i];
			break;
		}
	}

	if(!npc)
		return notify_fail("系统异常，请联系 管理员");

	key = "yqm/"+me->query("id");
	mapYQM = npc->query(key);

	if(!mapYQM)
	{
		printf("你目前没有可用的邀请码\n");
		return 1;
	}

	arrKey = keys(mapYQM);
	for(int i=0; i<sizeof(arrKey); i++)
	{
		code_user = mapYQM[arrKey[i]];
		if(code_user == "" && arg != "used")
		{
			printf(HIC "%s" NOR HIW "\t[可用]" NOR  "\n"
				, arrKey[i]);
		}
		if(code_user != "" && arg == "used")
		{
			printf(CYN "%s" NOR WHT "\t[已注册 %s]" NOR "\n"
				, arrKey[i], code_user);
		}
	}

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式： yqm [used]

这个指令让你查看你 可用/已用 的邀请码列表。
HELP
	);
	return 1;
}

