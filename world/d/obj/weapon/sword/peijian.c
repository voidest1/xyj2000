// cracked by vikee 2/09/2002   vikee@263.net
// 佩剑 


#include <weapon.h>

inherit "/d/obj/weapon/sword/anqi_container.c";

void create()
{
   set_name("佩剑", ({"pei jian","jian","sword"}));
   set_weight(4000);
   if( clonep() ) 
          set_default_object(__FILE__);
   else 
     {
      set("long", "一柄随身的佩剑，剑柄处似乎有些机关能装(install)些暗器进去。\n");
      set("orilong", "一柄随身的佩剑，剑柄处似乎有些机关能装(install)些暗器进去。\n");
      set("unit", "柄");
      set("value", 3000);
      set("material", "iron");
      set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
      set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
      set("anqi/allow", 1);
      set("anqi/max", 20);
      set("anqi/now", 0);
     }
     init_sword(20);
     setup();
}

