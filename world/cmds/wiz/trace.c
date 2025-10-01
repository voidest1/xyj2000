// trace.c

int main(object me, string arg)
{
	if(arg == "on")
	{
		me->set_temp("debug_ex/trace", 1);
		message_vision("系统 trace 信息已打开。\n", me);
	}
	else
	{
		me->set_temp("debug_ex/trace", 0);
		tell_object(me, "系统 trace 信息已关闭。\n");
	}
	return 1;
}

int help (object me)
{
write(@HELP
指令格式 : trace <on|off>

打开/关闭 trace 信息

HELP
     );
    return 1;
}
