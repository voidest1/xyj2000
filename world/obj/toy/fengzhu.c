

#include <ansi.h>
#include <armor.h>
inherit NECK;

void create()
{
        set_name(HIY"定风珠"NOR, ({"dingfeng zhu","dingfeng","zhu"}));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
		set("value", 2000);
		set("long", "一枚定风珠,似乎隐含着无限的力量。\n");
		set("no_sell", 1);
		set("no_put",1);
		set("no_drop",1);
		set("material", "steel");
		set("armor_prop/spells", 20);
		set("armor_prop/dodge", 20);
		set("armor_prop/parry", 20);
		set("armor_prop/armor", 1);
		set("armor_prop/attack",20);
	     set("armor_prop/unarmed",10);
		 set("armor_prop/sword",10);
		 set("armor_prop/blade",10);
		 set("armor_prop/spear",10);
		 set("armor_prop/whip",10);
		 set("armor_prop/fork",10);
		 set("armor_prop/rake",10);
		 set("armor_prop/mace",10);
	     set("armor_prop/staff",10);
		 set("armor_prop/stick",10);
		 set("armor_prop/axe",10);
		 set("armor_prop/hammer",10);
		 set("armor_prop/dagger",10);
		 set("armor_prop/throwing",10);
		
        }
	setup();
}

int query_autoload() { return 1; }
