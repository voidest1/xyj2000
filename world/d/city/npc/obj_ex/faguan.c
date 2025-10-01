// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit HEAD;

void create()
{
        set_name("天师法冠", ({ "loyal bonnet", "bonnet", "hat" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "顶");
		set("long", "一顶黄色象牙玉法冠。\n");
                set("material", "steel");
                set("value", 1000);
		set("no_sell", 1);
				set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
				set("no_give","总管发的装备，可不能乱送人哟！\n");
				set("no_get","想拿总管框框发的装备？做梦吧!\n");
                set("armor_prop/armor", 3);
		set("armor_prop/intelligence", 3);
		set("armor_prop/personality", 1);
        }
        setup();
}