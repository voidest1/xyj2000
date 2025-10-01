// cracked by vikee 2/09/2002   vikee@263.net
// callouts.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mixed *info;
	int i;
	string output;

//	output = sprintf("%-46s %20s %6s %s\n", "鐗╀欢", "鍑芥暟", "寤惰繜", "鍙傛暟"); 

	output = sprintf("%-20s %-6s %s\n", "鍑芥暟", "寤惰繜","鐗╀欢");

	if( arg && arg!="" )
		info = filter_array(call_out_info(), (: $1[1]==$2 :), arg);
	else
		info = call_out_info();

	for(i=0; i<sizeof(info); i++) {
		if ( sizeof(info[i]) == 4)
			output += sprintf("%-20s %-6d %O %O\n",info[i][1],info[i][2],info[i][0],info[i][3]);
/* 
			output += sprintf("%-46O %20s %6d %O\n",
				info[i][0], info[i][1], info[i][2], info[i][3] );
*/
		else

			output += sprintf("%-20s %-6d %O\n", info[i][1],info[i][2],info[i][0]);
/*
			output += sprintf("%-46O %20s %6d\n",
				info[i][0], info[i][1], info[i][2] );
*/
	}

	me->start_more(output);
	return 1;
}

int help()
{
	write(@LONG
鎸囦护鏍煎紡锛歝allouts [<鍑芥暟鍚嶇О>]

List all the system callouts, or, a particular callouts 
specified as a parameter.

LONG
	);
	return 1;
}