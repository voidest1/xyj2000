// cracked by vikee 2/09/2002   vikee@263.net
inherit NPC;

void create()
{
  set_name("小妖", ({"xiao yao","yao"}));
  set("gender", "男性");
  set("age", 10);
  set("long","一个贼眉鼠眼的小妖精。\n");
  set("combat_exp", 10000+random(3000));
  set("daoxing", 10000);

  set("per", 15);
  set_skill("dodge", 10);
  set_skill("parry", 10);
  set_skill("unarmed", 10);
  set("max_sen",200);
  set("max_gee",200);
  set("max_gin",200);
  set_skill("spells",10);
  set_skill("stick",10);
  set("chat_chance",2);
  set("chat_msg",({
        "小妖皱一皱小贼眉。\n",
        "小妖拼命地眨眨一对闪闪发光的小鼠眼。\n",
        "小妖一跳，叭叽一声摔在地上。\n",
        "小妖走到你面前，哇呀咿啊叫了几声。\n",
        "小妖嗖地一声，甩手倒挂在洞岩上。\n",
        "小妖一不小心，呀呀呀从洞岩上失手掉下来。\n",
    }));
  setup();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
  carry_object("/d/obj/weapon/stick/shuzhi")->wield();
}