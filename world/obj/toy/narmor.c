
#include <ansi.h>
#include <armor.h>

inherit EQUIP;
//inherit ARMOR;

string trans(string edes)
{
 
 string cdes;
 
	 
		 switch(edes)
		 {
		 case "armor_prop/dodge":			cdes="轻功";break;
		 case "armor_prop/parry":			cdes="招架";break;
         case "armor_prop/spells":			cdes="法术";break;
         case "armor_prop/strength":		cdes="体格";break;
	     case "armor_prop/constitution":	cdes="根骨";break;
	     case "armor_prop/intelligence":	cdes="悟性";break;
	     case "armor_prop/spirituality":	cdes="灵性";break;
		 case "armor_prop/composure":		cdes="定力";break;
		 case "armor_prop/courage":			cdes="胆识";break;
		 case "armor_prop/karma":			cdes="福缘";break;
		 case "armor_prop/personality":		cdes="容貌";break;
		 case "armor_prop/armor_vs_force":  cdes="御气";break;
		 case "armor_prop/attack":			cdes="攻击";break;
	     case "armor_prop/unarmed":			cdes="格斗";break;
		 case "armor_prop/sword":			cdes="剑法";break;
		 case "armor_prop/blade":			cdes="刀法";break;
		 case "armor_prop/spear":			cdes="枪法";break;
		 case "armor_prop/whip":			cdes="鞭法";break;
		 case "armor_prop/fork":			cdes="叉法";break;
		 case "armor_prop/rake":			cdes="耙法";break;
		 case "armor_prop/mace":			cdes="锏法";break;
	     case "armor_prop/staff":			cdes="杖法";break;
		 case "armor_prop/stick":			cdes="棍法";break;
		 case "armor_prop/axe":			    cdes="斧法";break;
		 case "armor_prop/hammer":			cdes="锤法";break;
		 case "armor_prop/dagger":			cdes="短兵";break;
		 case "armor_prop/throwing":	    cdes="暗器";break;
		 
		 }
	 
return cdes;
}


string *typ = ({
  "armor",
  "boots",
  "cloth",
  "finger",
  "hands",
  "head",
  "neck",
  "shield",
  "surcoat",
  "waist",
  "wrists",
});

string *names = ({
  "妖魔盔甲",
  "妖魔长靴",
  "妖魔战袍",
  "妖魔护指",
  "妖魔护掌",
  "妖魔头盔",
  "妖魔项链",
  "妖魔盾牌",
  "妖魔披风",
  "妖魔护腰",
  "妖魔护腕",
});

string *ids = ({
  "yaomo armor",
  "yaomo boots",
  "yaomo cloth",
  "yaomo finger",
  "yaomo hands",
  "yaomo kui",
  "yaomo necklace",
  "yaomo dun",
  "yaomo pifeng",
  "yaomo waist",
  "yaomo wrists",
});

string *ido = ({
  "armor",
  "boots",
  "cloth",
  "finger",
  "hands",
  "kui",
  "necklace",
  "dun",
  "pifeng",
  "waist",
  "wrists",
});


string *atta = ({
"armor_prop/dodge",
"armor_prop/parry",
"armor_prop/spells",
});

string *attb = ({
"armor_prop/strength",
"armor_prop/constitution",
"armor_prop/intelligence",
"armor_prop/spirituality",
"armor_prop/composure",
"armor_prop/courage",
"armor_prop/karma",
"armor_prop/personality",
});



void setg(string msg)
{
int x,y,numa,numb;

x=random(3);
y=random(8);
numa=5+random(5);
numb=2+random(2);
set(atta[x],numa);
set(attb[y],numb);


msg+=trans(atta[x])+"+"+numa+"\n";
msg+=trans(attb[y])+"+"+numb+"\n";
msg=HIG+msg+NOR;
set("long",msg);
set("equip_level",1);
return;

}

void setb(string msg)
{
 int x,y,z;
 int numa,numb,numc;
 
 numa=7+random(5);
 numb=3+random(3);
 numc=3+random(3);
 x=random(3);
 set(atta[x],numa);
 y=random(8);
 do {z=random(8);} while ( y==z );
	 
 set(attb[y],numb);
 set(attb[z],numc);


 msg+=trans(atta[x])+"+"+numa+"\n";
 msg+=trans(attb[y])+"+"+numb+"\n";
 msg+=trans(attb[z])+"+"+numc+"\n";

 msg=HIB+msg+NOR;
 set("long",msg);
 set("equip_level",2);
 return;
}


void setr(string msg)
{
	int x,y,z;
	int numa,numb,numc,numd;
    
	x=random(3);
	z=1+random(7);
    do {y=random(3);} while ( y==x );
	//do {z=random(8);} while ( y==z );
    numa=10+random(8);
	numb=10+random(8);
	numc=5+random(4);
    numd=5+random(4);
    
	set(atta[x],numa);
	set(atta[y],numb);
	set(attb[0],numc);
    set(attb[z],numd);


	msg+=trans(atta[x])+"+"+numa+"\n";
	msg+=trans(atta[y])+"+"+numb+"\n";
	msg+="体格+"+numc+"\n";
	msg+=trans(attb[z])+"+"+numd+"\n";
	msg=HIR+msg+NOR;

    set("long",msg);
	set("equip_level",3);
	return;

}

void setm(string msg)
{   
	int x;
	int numa,numb,numc,numd,nume;

	x=1+random(7);

	numa=20+random(10);
	numb=20+random(10);
	numc=20+random(10);
	numd=10+random(5);
	nume=10+random(5);
    
	set(atta[0],numa);
	set(atta[1],numb);
	set(atta[2],numc);
    set(attb[0],numd);
	set(attb[x],nume);
	

    msg+="轻功+"+numa+"\n";
	msg+="招架+"+numb+"\n";
	msg+="法术+"+numc+"\n";
	msg+="体格+"+numd+"\n";
	msg+=trans(attb[x])+"+"+nume+"\n";
	msg=HIM+msg+NOR;

	set("long",msg);
	set("equip_level",4);
	return;

}



void create()
{  
	

   int i,j;
   string msg;
   set("unit", "件");
   set("value", 40000);
   set("material", "bone");
   msg="这是一件妖魔遗落的防具，发着幽幽的光。\n"+"装备属性：\n";
  i = random(sizeof(names));
  j = random(100);
  
  if ( j < 100 && j >= 40 )
  {
  
  set_name(HIG+names[i]+NOR, ({ids[i], ido[i], "yaomo fangju"}));
  set("armor_type",typ[i]);
  set("armor_prop/armor", 7+random(5));set_weight(1000);
  if (i==2 || i==8 || i==7) {set_weight(3000);set("armor_prop/armor", 25+random(5));}
  if (i==0 ) {set_weight(6000);set("armor_prop/armor", 50+random(5));}
 

  setg(msg);

  }
  else if ( j <40 && j>=10 ) 
  {
  set_name(HIB+names[i]+NOR, ({ids[i], ido[i], "yaomo fangju"}));
  set("armor_type",typ[i]);
  set("armor_prop/armor", 10+random(8));set_weight(1000);
   if (i==2 || i==8 || i==7) {set_weight(3000);set("armor_prop/armor", 30+random(8));}
   if (i==0 ) {set_weight(6000);set("armor_prop/armor", 60+random(8));}

  setb(msg);

  }
  else if ( j <10 && j>=1 ) 
  {
  set_name(HIR+names[i]+NOR, ({ids[i], ido[i], "yaomo fangju"}));
  set("armor_type",typ[i]);
  set("armor_prop/armor", 13+random(12));set_weight(1000);
   if (i==2 || i==8 || i==7) {set_weight(3000);set("armor_prop/armor", 40+random(12));}
   if (i==0 ) {set_weight(6000);set("armor_prop/armor", 66+random(12));}

  setr(msg);

  }
 else if (j==0)
 {
  set_name(HIM+names[i]+NOR, ({ids[i], ido[i], "yaomo fangju"}));
  set("armor_type",typ[i]);
  set("armor_prop/armor", 20+random(15));set_weight(1000);
   if (i==2 || i==8 || i==7) {set_weight(3000);set("armor_prop/armor", 55+random(15));}
   if (i==0 ) {set_weight(6000);set("armor_prop/armor", 80+random(15));}

  setm(msg);
  }

  set("no_sell",1);
  
  setup();
}




