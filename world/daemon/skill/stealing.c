// cracked by vikee 2/09/2002   vikee@263.net
// perception.c
#include <ansi.h>

inherit SKILL;

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "璐煎ご璐艰剳" NOR,     
		HIB "璐兼墜璐艰剼" NOR,
		HIB "蹇墜蹇剼" NOR,     
		CYN "鍑烘墜濡傞" NOR,
		HIC "鎵嬪埌鎿掓潵" NOR,     
		HIW "濡欐墜绁炲伔" NOR,
	});

	grade = level / 10;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}