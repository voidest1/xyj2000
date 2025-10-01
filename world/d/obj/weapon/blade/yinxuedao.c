//by hexiu 20130616
#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name(RED"饮血刀"NOR, ({"yinxue dao", "dao"}));

        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "一把刀身暗红的长刀，刀把上镶嵌有红宝石。\n");
             set("no_give", 1);
             set("no_sell", 1);
             set("no_drop", 1);
             set("no_put", 1);
                set("value", 2500);
                set("material", "gold");
                set("wield_msg", "$N「唰」地一声抽出一把$n握在手中！\n");
                set("unwield_msg", "$N将手中的$n插入刀鞘。\n");
        set("weapon_prop/courage", 15);

        }
        init_blade(80);
        setup();
}
int query_autoload() { return 1; }

mixed hit_ob(object me, object victim,int damage_bonus,int gp)
{if (50<random(100)) return 0;
        gp=(int)(random(damage_bonus/4));
if (gp < 1) gp=1;if (gp > 100) gp=100;
message_vision(HIR"$N手中饮血刀一道暗红闪过。\n"NOR,me,victim);
if(wizardp(me)) tell_object(me,HIY"吸血量："+gp+"\n"NOR);
//if( (int)me->query("kee")  < 3*(int)me->query("max_kee")/2 ) me->add("kee", gp);
	call_out("leech",1,me,gp);
return gp;}
void leech(object me,int gp)
{if (!living(me)) return;
if( (int)me->query("kee")  > 3*(int)me->query("max_kee")/2 )
{message_vision(HIR"\n$N红光黯淡下来！\n"NOR,me);return;}
else {me->add("kee", gp);
message_vision(HIR"\n$N觉得气血有所恢复！\n"NOR,me);
if(wizardp(me)) tell_object(me,HIR"吸血量："+gp+"\n"NOR);
return;}
}



