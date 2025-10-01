// cracked by vikee 2/09/2002   vikee@263.net
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string key, chinz;

	if( !arg || arg=="" )
		return notify_fail("鎸囦护鏍煎紡锛歝hinese <鑻辨枃>==<涓枃>\n");

	if( sscanf(arg, "%s==%s", key, chinz)==2 ) {
		CHINESE_D->add_translate(key, chinz);
		write( key + " == " + chinz + "\nOk.\n");
		return 1;
	}

	return 0;
}

int help()
{
	write ( @HELP
鎸囦护鏍煎紡锛歝hinese <鑻辨枃>==<涓枃>
HELP
	);
	return 1 ;
}