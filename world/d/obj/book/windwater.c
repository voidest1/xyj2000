// cracked by vikee 2/09/2002   vikee@263.net
// nowords.c
//cglaem...12/16/96.

inherit ITEM;

void init();
void tear();

void create()
{
        set_name("〖风水〗", ({"book","shu"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
	set("long",
	"一本脏兮兮的小册子。上面划着一地形之类的图案。\n");
        set("material", "paper");
        set("value", 100);
        set("skill", ([
                        "name": "spells",
                        "sen_cost": 20,
                        "difficulty": 25,
                        "max_skill": 20,
]) );
        }
	setup();
}


