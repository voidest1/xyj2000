// cracked by vikee 2/09/2002   vikee@263.net
inherit __DIR__"piggy_two.c";

void create()
{
    ::create();

    set ("short", "双人拱猪房");
    set("exits", ([
        "west": __DIR__"club3",
    ]) );
}
