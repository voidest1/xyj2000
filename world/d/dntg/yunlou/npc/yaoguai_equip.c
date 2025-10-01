
string give_equip(object me,object guai) 
{
  int lev;
  string q_level;
  object eq;
  
  
  if ( random(me->query("combat_exp")*2) > guai->query("combat_exp")+random(guai->query("combat_exp")) )
  {
  eq=new("/obj/toy/narmor.c");
  lev=eq->query("equip_level");
  q_level=eq->query("armor_type")+" "+chinese_number(lev);
  
  if (lev == 4 )
	 { 
	  command_function("rumor "+ 
	    "听说"+me->query("name")+"降服了"+guai->query("name")+"获得了意外惊喜！");
	 }
	  else
	  {
		  command_function("rumor "+ 
	    "听说"+me->query("name")+"降服了"+guai->query("name")+"获得了意外收获！");
	  }
  
	  
	  if (eq->move(me))
      {
	  tell_object(me,"你得到了一件装备！\n");
	  }
      else 
	  {
		  if(eq->move(environment(guai)))
             tell_object(environment(guai),"一件装备掉了下来！\n");
		  else
		  {
			  eq->move("/d/city/kezhen.c");
			  tell_object(environment(eq),
                        "砰地一声，天上掉下一个东西！\n");

		  }

	  }
	  return q_level;
  }

  return "qnone";
}