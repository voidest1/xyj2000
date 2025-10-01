// cracked by vikee 2/09/2002   vikee@263.net
// pill.c

inherit COMBINED_ITEM;

void setup()
{
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	if( !id(arg) ) return notify_fail("浣犺鍚冧粈涔堬紵\n");
	
}