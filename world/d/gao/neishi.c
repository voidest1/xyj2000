// cracked by vikee 2/09/2002   vikee@263.net
// neishi.c
#include <room.h>
inherit ROOM;

void create()
{
  set ("short", "鍐呭");
  set ("long", @LONG

鎴块棿涓嶅ぇ锛屽嵈鏄煶闂ㄧ煶绐楋紟绐椾笂杩樻湁閾佹墦鐨勬煴瀛愶紟瑕佹槸澶ч棬
涓嶅紑锛岀湅鏉ユ槸娌℃硶鍑哄幓鐨勶紟
LONG);

set("exits", ([ /* sizeof() == 4 */
"west" : "/d/gao/room",
]));

 set("objects", ([ /* sizeof() == 2 */
"/d/gao/obj/xiaojie" : 1,

]));

	create_door("west", "鐭抽棬", "east", DOOR_CLOSED);

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

