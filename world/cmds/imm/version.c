// cracked by vikee 2/09/2002   vikee@263.net
// version.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	write(__VERSION__+"\n");
	return 1;
}
int help(object me)
{
  write(@HELP
鎸囦护鏍煎紡 : version
 
杩欎釜鎸囦护浼氭樉绀烘父鎴忕洰鍓嶆墍鐢ㄧ殑 MudOS driver 鐗堟湰.
 
HELP
    );
    return 1;
}
 