// cracked by vikee 2/09/2002   vikee@263.net
// by snowcat 11/22/1997

#include <armor.h>

inherit WRISTS;

void create()
{
  set_name("鎏金腕链", ({ "liujin wanlian", "wanlian", "wrists" }));
  set("weight", 200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "个");
    set("value", 5000);
    set("material", "gold");
    set("armor_prop/armor", 1);
  }
  setup();
}
