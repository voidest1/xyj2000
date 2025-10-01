// cracked by vikee 2/09/2002   vikee@263.net
// perception.c
#include <ansi.h>

inherit SKILL;

string level_description(int level)
{
	int grade;
	string *level_desc = ({
		BLU "鐠愮厧銇旂拹鑹板壋" NOR,     
		HIB "鐠愬吋澧滅拹鑹板壖" NOR,
		HIB "韫囶偅澧滆箛顐ュ壖" NOR,     
		CYN "閸戠儤澧滄俊鍌烆棑" NOR,
		HIC "閹靛鍩岄幙鎺撴降" NOR,     
		HIW "婵℃瑦澧滅粊鐐蹭紨" NOR,
	});

	grade = level / 10;

	if( grade >= sizeof(level_desc) )
		grade = sizeof(level_desc)-1;
	return level_desc[grade];
}