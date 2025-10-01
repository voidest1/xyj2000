// cracked by vikee 2/09/2002   vikee@263.net
#include <ansi.h>

inherit SSERVER;

int scribe(object me,object ob)
{
	object seal;

	if( (int)me->query("mana") < 100)
		return notify_fail("浣犵殑娉曞姏涓嶈冻銆俓n");
	if( (int)me->query("sen") < 100)
		return notify_fail("浣犵殑绮剧鏃犳硶闆嗕腑銆俓n");
	
	
	message_vision("$N鍜牬鎵嬫寚锛屼几鎵嬪湪妗冪绾镐笂鐢讳簡鍑犱笅銆俓n", me);
	
	destruct(ob);

	seteuid(getuid());
	seal=new("/u/rainy/jjf/follow_seal");
	seal->move(me);
	seal->invocation(me);

	me->start_busy(2);
	return 1;
}