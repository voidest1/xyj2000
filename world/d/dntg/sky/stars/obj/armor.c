// cracked by vikee 2/09/2002   vikee@263.net
// jinjia.c 金甲
#include <armor.h>
#include "self_destruct.c"

inherit ARMOR;

void create()
{
        set_name("战甲", ({"armor"}));
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("long", "一件战甲．\n");
                set("material", "steel");
                set("value", 200);
                set("armor_prop/armor", 55);
        }
        setup();
}


