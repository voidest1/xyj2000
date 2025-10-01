
//inherit ITEM;

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("歼十五战斗机", ({"fighter", "j15 fighter","sword"}));
	set_weight(200000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "架");
		set("long", "这是一架歼十五舰载战斗机！\n");
		set("value", 200000);
		set("material", "steel");
		set("no_get",1);
		set("no_put",1);
		//set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		//set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(225);
	setup();
}