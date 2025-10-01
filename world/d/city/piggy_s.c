// cracked by vikee 2/09/2002   vikee@263.net
inherit __DIR__"piggy.c";

void create()
{
    ::create();

    set ("short", "閹疯京灏撻崡妤佸煣");
    set("exits", ([
        "north": __DIR__"club3",
    ]) );
}
