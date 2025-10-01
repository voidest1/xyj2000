// cracked by vikee 2/09/2002   vikee@263.net
// Room: some place in 瑗跨墰璐烘床
// inside2.c

inherit ROOM;
inherit "/d/wiz/no_get";

void create()
{
  set ("short", "鍗у");
  set ("long", @LONG

鑰佺浠欎篃瑕佺潯瑙夛紟鍦ㄨ繖浣犲氨灏芥儏鐨勭潯鍚э紟

LONG);
set("exits", ([ /* sizeof() == 4 */
"north": __DIR__"inside2",
]));

        set("no_clean_up", 0);
        set("sleep_room",1);
        set("if_bed",1);

  set("no_magic",1);
        setup();
}



