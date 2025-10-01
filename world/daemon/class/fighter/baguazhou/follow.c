// cracked by vikee 2/09/2002   vikee@263.net
#include <ansi.h>

inherit SSERVER;

int scribe(object me,object ob)
{
	object seal;

	if( (int)me->query("mana") < 100)
		return notify_fail("娴ｇ姷娈戝▔鏇炲娑撳秷鍐婚妴淇搉");
	if( (int)me->query("sen") < 100)
		return notify_fail("娴ｇ姷娈戠划鍓ь殻閺冪姵纭堕梿鍡曡厬閵嗕繐n");
	
	
	message_vision("$N閸滎剛鐗幍瀣瘹閿涘奔鍑犻幍瀣躬濡楀啰顑佺痪闀愮瑐閻㈣绨￠崙鐘辩瑓閵嗕繐n", me);
	
	destruct(ob);

	seteuid(getuid());
	seal=new("/u/rainy/jjf/follow_seal");
	seal->move(me);
	seal->invocation(me);

	me->start_busy(2);
	return 1;
}