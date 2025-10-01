// cracked by vikee 2/09/2002   vikee@263.net
// snowcat 4/25/97

#include <weapon.h>

inherit THROWING;

void create()
{
  set_name("●金丹砂●", ({"jindan sha", "sha"}));
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("long", "一些闪闪发光的金丹砂。\n");
    set("unit", "些");
    set("base_unit", "颗");
    set("base_weight", 40);
    set("base_value", 1);
  }
  //set("is_monitored",1);
  set_amount(18);
  //set("rigidity",100);
  set("never_tear",1);
	set("no_sell",1);
	set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
	set("no_give","总管发的装备，可不能乱送人哟！\n");
	set("no_get","想拿总管框框发的装备？做梦吧!\n");
  init_throwing(180);
  setup();
}