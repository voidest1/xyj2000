// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>
#include "self_destruct.c";

inherit BOOTS;

void create()
{
        set_name( "鞋", ({ "shoes" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "双");
                set("long", "一双青布鞋。");
                set("value", 100);
                set("material", "boots");
                set("armor_prop/dodge", 3);
        }
        setup();
}
