// cracked by vikee 2/09/2002   vikee@263.net
#pragma optimize

#include "/adm/simul_efun/atoi.c"
#include "/adm/simul_efun/chinese.c"
#include "/adm/simul_efun/gender.c"
#include "/adm/simul_efun/object.c"
#include "/adm/simul_efun/path.c"
#include "/adm/simul_efun/wizard.c"

// This must be after gender.c
#include "/adm/simul_efun/message.c"
#include "/adm/simul_efun/file.c"

void create()
{
	seteuid(getuid());
	write("simul_efun loaded successfully.\n");
}