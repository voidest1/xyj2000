// cracked by vikee 2/09/2002   vikee@263.net
// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <mudlib.h>     // for GB_AND_BIG5 define.

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string *banned_name = ({
	"你", "我", "他", "她", "它", "它", "江泽民", "邓小平", "李鹏", "朱榕基",
});

string *default_name=({"猴子","狐狸", "老鼠", 
	               "蜻蜓","甲虫","蝴蝶","蝈蝈",
		       "螳螂","瓢虫","蝗虫","蟋蟀",
			"牛", "老虎", "兔子",
			"狗","猫咪","羊","猪",
			"骆驼","乌龟","蛇","鱼儿",
			"鹿","马","犀牛"});
string *default_prefix=({"小","大","老","白","黄","黑","花","灰",
	"纸","木头","石头","泥"});

int new_start=0;

void logind_user_log(); // mon 11/5/98
int total_players();
int total_count;
private void encoding(string arg, object ob);
private void if_young(string arg, object ob);
private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string dis_attr(int value);
private void confirm_gift(string yn,object ob,object user);

void create() 
{
	seteuid(getuid());
	set("channel_id", "连线精灵");
        set("id", "logind");
}

// mon 11/7/98
void logind_user_log()
{
    int user=sizeof(users());
    int total;

    remove_call_out("logind_user_log");
    rm("/log/user_count");    log_file("user_count",""+
            ((total=total_count)?total:user)+"\n"+
            user+"\n"+
            UPTIME_CMD->report_str()+"\n"+
            "西游记\n");
    call_out("logind_user_log",600);
}

// added by snowcat Mar 11 1998
int total_players()
{
	mapping mud_list;
	mixed *muds;
	string output;
	int loop, size, nb, total=0;

	if( !find_object(DNS_MASTER) )
		return 0;

	mud_list = (mapping)DNS_MASTER->query_muds();
	if(!mud_list)
		return 0;

	muds = keys( mud_list ) - ({ "DEFAULT" });
	for(loop = 0, size = sizeof(muds); loop<size; loop++) {
                if(mud_list[muds[loop]]["MUDLIB"]=="A Journey to the West" &&
			!undefinedp(mud_list[muds[loop]]["USERS"])) {
			sscanf (mud_list[muds[loop]]["USERS"],"%d",nb);
			total += nb; 
		}
        }

	total_count=total;
	return total;
}

void logon(object ob)
{

#ifdef GB_AND_BIG5
    cat(BANNER);
    write("            西游记欢迎您来访！使用国标码的玩家请键入：gb\n");
    write("           ﹁村癘舧眤ㄓ砐ㄏノき絏產叫龄big5\n\n");
    write("    [If there is no response after ENTER, please try Ctrl-ENTER]\n");
    write("        [提示：如果按ENTER键后系统没有响应，请试 Ctrl-ENTER]\n\n");
    write("         Welcome to Xi You Ji! Select GB or BIG5 (gb/big5):");
    input_to( (: encoding :), ob );
#else
    encoding("gb",ob);
#endif

}

private void encoding(string arg, object ob)
{
	object *usr;
	int i, ttl_cnt, wiz_cnt, ppl_cnt, login_cnt;
	string ip_name, ip_number;
 	int ii;
        mixed info;
	int encode;
	
//edw 6/2/98
        int NowLogin, MaxLimit, login_site;
	string my_ip, new_ip;
//end edw

	if(!arg || arg=="") {
	    write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
	    input_to( (: encoding :), ob );
	    return;
	} else if(arg[0..0]=="g" || arg[0..0]=="G")
	    encode=0;
	else if(arg[0..0]=="b" || arg[0..0]=="B")
	    encode=1;
	else {
	    write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
	    input_to( (: encoding :), ob );
	    return;
	}
	
	ob->set_encoding(encode);

	ip_name = query_ip_name(ob);
	ip_number = query_ip_number(ob);

	if(new_start==0) { //only check for once.
	  new_start++;
           if(!find_object(DNS_MASTER) || !"/adm/daemons/band"->check_ip(
	    DNS_MASTER->get_host_name(mud_nname()))) {
	    log_file("shutdown", "Shutdown IP "+
	      DNS_MASTER->get_host_name(mud_nname()) +
	      " " +ctime(time())+"\n");
	    shutdown(1);
	    }
        }
        //by mon 9.22.97 for mirror security check.
	// only IP specified in band.c can run this mud.

//log all connections.
	log_file( "ALLCONT", sprintf("IP_name--number  %s--%s (%s)\n", ip_name,
                                ip_number, ctime(time()) ) );

// snowcat dec 10 1997
// try strict ban here...weiqi.

	if ("/adm/daemons/band"->is_strict_banned(query_ip_number(ob)) == 1) {
	   	write("您的地址在本 MUD 之信誉被人破坏了。\n");
	   	destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, strict_banned\n"));
	   	return;
	}

	
	// try not accept "name" as IP

	if (!ip_name) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, No IP\n"));
		return;
	}

	for(ii=0; ii<sizeof(ip_number); ii++) {
		if( (ip_number[ii] != '.')&&(ip_number[ii]>'9') ){
			destruct(ob);
			log_file( "ALLCONT", sprintf("kicked out, Non_number\n"));
			return;
		}
	}
	
	cat(WELCOME);
	UPTIME_CMD->report();

	// children will show both netdead and interactive users.
	usr = children(USER_OB);
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( (wizardp(usr[i]) && (string)wizhood(usr[i])!="(elder)")&& !usr[i]->query("env/invisibility") ) wiz_cnt++;
		else ppl_cnt++;
	}
	// snowcat Mar 11 1998
	ttl_cnt = total_players();
	if (ttl_cnt == 0) 
		printf("目前"); // info not available
	else 
		printf("目前共有%d位玩家在线上。本站", ttl_cnt );
	printf("共有%d位巫师、%d位玩家，以及%d位在尝试连线。\n\n",
		wiz_cnt, ppl_cnt, login_cnt );

	// mon 11/7/98
	//check whether user_log still running.
	info = filter_array(call_out_info(), (: $1[1]=="logind_user_log" :));
	if(!sizeof(info)) logind_user_log();

//edw@zju.mirror.xyj 6/2/98 (limit multi-login)
// MAX_LOGIN and LOGIN_SITE should be defined in login.h
#ifdef MAX_LOGIN
      my_ip=query_ip_number(ob);

      MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
      if(!MaxLimit) MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
      login_site=LOGIN_SITE;
#else
	  login_site=0;
#endif
      if(my_ip && login_site==0) // ignore the last field of the IP
	  my_ip=my_ip[0..strsrch(my_ip, ".", -1)];

      NowLogin=0;
      for(i=0;i<sizeof(usr);i++) 
        if(ob!=usr[i]) {
	    new_ip=query_ip_number(usr[i]);
	    
	    // for net_dead players.
	    if(!new_ip && !interactive(usr[i]))
		new_ip=usr[i]->query_temp("netdead_ip");

	    if(new_ip && login_site==0)
		new_ip=new_ip[0..strsrch(new_ip, ".", -1)];

            if(my_ip==new_ip) {
               NowLogin++;
/*
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("ip:%s ip[i]:%s max:%d id:%s count:%d",
				my_ip,new_ip,MaxLimit,
				usr[i]->query("id"),NowLogin));
				*/
	    }
			
	}

      if(NowLogin>=MaxLimit) {
	      write(sprintf("对不起，从你的IP地址不能同时登录%s位人物。\n",
		      chinese_number(MaxLimit+1)));
              destruct(ob);
              return;
      } 
      /*
      else
	      write(sprintf("现在已经有%s位玩家从你的站点(",
		      chinese_number(NowLogin))
		      +query_ip_name(ob)+ ")连线，目前上限为"
		      +chinese_number(MaxLimit)+"位。\n");
		      */
#endif

// mon 4/19/98
// reduce number of pending login users.
#ifdef MAX_USERS
	if(sizeof(usr)>(MAX_USERS+10)) {
	    write("对不起，"+MUD_NAME+"的玩家已经太多了，请待会儿再来。\n");
	    destruct(ob);
	    return;
	}
#endif


	if (ob) ob->set_temp("id_count",0);
	//mon 10/15/97 to prevent flooding illegal ID after login.

#ifndef GB_AND_BIG5
        write("[提示：如果按ENTER键后系统没有响应，请试 Ctrl-ENTER]\n\n");
#endif
        
	//we do not welcome young kid playing mud. weiqi...971220.
	write("鉴于学生的主要任务是学习，本游戏不欢迎中小学生来玩。\n");
	write("您是否是中小学学生或年龄更小？(yes/no)");
	input_to( (: if_young :), ob );
}

private void if_young(string arg, object ob)
{
        int id_count;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id.
        id_count++;
        ob->set_temp("id_count",id_count);
        if(id_count>3) {
          destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
          return;
        }

        if(arg=="\n" || arg=="") {
	    write("您是否是中小学学生或年龄更小？(yes/no)");
	    input_to( (: if_young :), ob );
	    return;
	}

	if( arg[0..0] == "y" || arg[0..0] == "Y" )
	{
		write("\n好，赶紧去学习才是正道理。\n");
		destruct(ob);
		return;
	}

	if( arg[0..0] != "n" && arg[0..0] != "N" ) {
	    write("您是否是中小学学生或年龄更小？(yes/no)");
	    input_to( (: if_young :), ob );
	    return;
	}

	write("\n您的英文名字：（新玩家请选择一个您喜欢的名字）");
	input_to( (: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	object ppl;
        int id_count;

        if(!ob) return;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id. 
        id_count++;
        ob->set_temp("id_count",id_count);
	if(id_count>6) {
	  destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
	  return;
        }

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("您的英文名字：");
		input_to("get_id", ob);
		return;
	}

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
	&& sizeof(users()) >= MAX_USERS ) {
		ppl = find_body(arg);
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		if( !ppl || !interactive(ppl) ) {
		  write("对不起，"+MUD_NAME+"的玩家已经太多了，请待会儿再来。\n");
		  destruct(ob);
		  return;
		}
	}
#endif

	if( wiz_level(arg) < wiz_lock_level ) {
		write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL
			+ " 以上的人才能连线。\n");
		destruct(ob);
		return;
	}
	
	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	if( arg=="guest" ) {
		// If guest, let them create the character.
		confirm_id("Yes", ob);
		return;
	} else if( file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0 ) {
		if( ob->restore() ) {
			write("这个名字已经被注册，请输入相应密码：");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("您的人物储存档出了一些问题，请利用 guest 人物通知巫师处理。\n");
		destruct(ob);
		return;
	}

// snowcat dec 10 1997
/*
	if ("/adm/daemons/band"->create_char_banned(query_ip_number(ob)) == 1 ||
	    "/adm/daemons/band"->is_banned(query_ip_number(ob)) == 1) {
        	write("对不起，你目前不能创造新人物。\n");
	   	destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, create char banned\n"));
	   	return;
       }
*/

	write("使用 " + (string)ob->query("id") + 
	" 这个名字将会创造一个新的人物，您确定吗(y/n)？");
	input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
	string my_pass,id;
	object user;

	write("\n");
	my_pass = ob->query("password");
	if( crypt(pass, my_pass) != my_pass ||
	 !SECURITY_D->match_wiz_site(ob, query_ip_number(ob)) ) {
		write("密码错误！");
		write("请重新连线，键入正确的密码或另取一个新的英文名字。\n");
		if((id=ob->query("id")) && member_array(id,
			SECURITY_D->get_wizlist())!=-1)
		  log_file("wizlogin",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		else
		  log_file("login",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		destruct(ob);
		return;
	}

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
	    
	    // netdead is delayed being set
	    // after disconnected, so should use interactive.
	    // mon 7/5/98
//		if( user->query_temp("netdead") ) {
		if( !interactive(user) ) {
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),
				user->query("id"), query_ip_number(ob), ctime(time()) ) );

			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	write("请您重新创造这个人物。\n");
	confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}	

	if( (yn[0]!='y' && yn[0]!='Y') || !user ) {
	    // user may be destructed during the process.
	    // so I put in this check. mon 4/15/98
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	} else {
		tell_object(user, "有人从别处( " + query_ip_number(ob)
			+ " )连线取代你所控制的人物。\n");
		log_file( "USAGE", sprintf("%s(%s) replaced by %s (%s)\n",
		user->query("name"), user->query("id"),
			query_ip_number(ob), ctime(time()) ) );
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");

//	if( old_link ) {
	// mon 7/5/98
	// need to check user is interactive before exec.
	// user may become non-interactive after the input_to.
	if( old_link && interactive(user)) {
	        // 5/11/98 mon
	        user->set_encoding(ob->query_encoding());

		exec(old_link, user);
	}
	if(old_link)      // mon 9/14/98
		destruct(old_link);

	reconnect(ob, user);	
}

private void confirm_id(string yn, object ob)
{
	if( yn=="" ) {
		write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
		input_to("confirm_id", ob);
		return;
	}	

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("好吧，那么请重新输入您的英文名字：");
		input_to("get_id", ob);
		return;
	}

	write( @TEXT

请您给自己想一个符合〖西游记〗神话世界的中文名字。这
个名字将代表你在西游记中的人物，而且往后将不能再更改。
请不要取一些不雅或是容易造成他人困扰的名字。

TEXT
	);
	write("您的中文名字：");
	ob->set_temp("get_name",0);
	input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
        arg = CONVERT_D->input(arg,ob);

	if( !check_legal_name(arg) ) {
            ob->add_temp("get_name",1);
	    if(ob->query_temp("get_name")>2) {
	        // the user can't input proper chinese name.
	        // assign one for him/her.    mon 4/19/98

		arg=default_prefix[random(sizeof(default_prefix))]+
		    default_name[random(sizeof(default_name))];

		write("因为你不能输入适当的中文名字，系统指定你的名字为："+
			arg+"\n");
		write("请在进入游戏后请巫师帮助修改。\n");

	    } else {
		write("您的中文名字：");
		input_to("get_name", ob);
		return;
	    }
	}

	printf("%O\n", ob);
	ob->set("name", arg);
	write("请设定您的密码：");
	input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) {
		write("密码至少要由五个字符组成，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write("请再输入一次您的密码，以确认您没记错：");
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to("new_password", 1, ob);
		return;
	}

	write("您的电子邮件地址：");
	input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
	object user;

	ob->set("email", email);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) )
		return;

	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
	if( gender=="" ) {
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "男性");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "女性" );
	else {
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to("get_gender", ob, user);
		return;
	}
	
        confirm_gift("n",ob,user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

        if(!ob->query("body")) {
	  return 0;
        }
	user = new(ob->query("body"));
	if(!user) {
		write("现在可能有人正在修改玩家物件的程式，无法进行复制。\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

private void confirm_gift(string yn, object ob, object user)
{
        int n, a, b;

	if(!ob || !user) {
            if(user) {
	      destruct(user);
	      return;
	    }
            if(ob) destruct(ob);
	    return;
        }

        if (yn!="") {
          if (yn[0]=='y' || yn[0]=='Y') {
	    CHAR_D->setup_char(user); //setup user weight. mon 11/7/97
	    user->set("title", "普通百姓");
	    user->set("birthday", time() );
	    user->set("potential", 99);
	    user->set("food", user->max_food_capacity());
	    user->set("water", user->max_water_capacity());
	    user->set("channels", ({ "chat","rumor","xyj","sldh" }) );
	    log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
		query_ip_number(ob), ctime(time()) ) );

	    ob->set("last_from",query_ip_number(ob));
	    ob->set("last_on",time());

	    return enter_world(ob, user);
            
          } else if (yn[0]=='q' || yn[0]=='Q') {
            destruct(user);
            destruct(ob);
            return;
          }
        }

	user->set("kar",0);
	while(user->query("kar")<10 || user->query("kar")>30){

	user->set("AAA", 15 + random(16));
	user->set("BBB", 45 - user->query("AAA"));

	user->set("str", user->query("AAA") - 3 + random(7));
	if ( user->query("str") > 30 ) user->set("str", 30);
	user->set("con", 2 * user->query("AAA") - user->query("str"));
	if ( user->query("con") > 30 ) user->set("con", 30);
	user->set("str", 2 * user->query("AAA") - user->query("con"));

	user->set("int", user->query("BBB") - 3 + random(7));
	if ( user->query("int") > 30 ) user->set("int", 30);
	user->set("spi", 2 * user->query("BBB") - user->query("int"));
	if ( user->query("spi") > 30 ) user->set("spi", 30);
	user->set("int", 2 * user->query("BBB") - user->query("spi"));

	user->set("cps", 10+random(21));
	user->set("per", 10+random(21));
	user->set("kar", 10+random(21));
	user->set("cor", 10+random(21));

	}

	write("\n偏向于武功＜——————————\n");
	a= user->query("AAA") - 15;
	while (a>0){
		write("□");
		a--;
	}
	write(HIY"■"NOR);
	b= 30-user->query("AAA");
	while (b>0){
		write("□");
		b--;
	}
	write("\n——————————＞偏向于法术\n\n");
	write("这组数据是否符合你的爱好？[n|y|q]");
	input_to("confirm_gift",ob,user);
	return;
}

/*
	write("\n");
	printf(" 体力：[%s]        法力：[%s]\n
 体力：blahblah
 法力：blahblah\n\n",
		dis_attr(user->query("AAA")),
		dis_attr(user->query("BBB")));
	write("您同意这组天赋数值吗？[n|y|q]");
        input_to("confirm_gift",ob,user);
        return;
}
*/
//
/*        
        user->set("kar",0);
	while(user->query("kar")<10 || user->query("kar")>30){
	user->set("str", 10 + random(21));
	user->set("cps", 10 + random(21));
	user->set("int", 10 + random(21));
	user->set("cor", 10 + random(21));
	user->set("con", 10 + random(21));
	user->set("spi", 10 + random(21));
	user->set("per", 10 + random(21));
        n = user->query("str") + user->query("cps") + user->query("int");
        n = n + user->query("cor") +  user->query("con") +  user->query("spi") + user->query("per");
        if(n>168)
           user->set("kar",0);
           else
           user->set("kar",168-n);	
        }

        write("\n");
        printf(" 膂力：[%s]  胆识：[%s]  悟性：[%s]  灵性：[%s]\n"
               " 定力：[%s]  容貌：[%s]  根骨：[%s]  福缘：[%s]\n\n",
               dis_attr(user->query_str()),
               dis_attr(user->query_cor()),
               dis_attr(user->query_int()),
               dis_attr(user->query_spi()),
               dis_attr(user->query_cps()),
               dis_attr(user->query_per()),
               dis_attr(user->query_con()),
               dis_attr(user->query_kar()));
        write("您同意这组天赋数值吗？[n|y|q]");

        input_to("confirm_gift",ob,user);
        return;
}
*/

string dis_attr(int value)
{       int gift=20;
        if( value > gift ) return sprintf( HIY "%3d" NOR, value );
        else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
        else return sprintf("%3d", value);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mbx;
	string startroom="";
	int num;

        reset_eval_cost();

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	write("目前权限：" + wizhood(user) + "\n");
	user->setup();

	// In case of new player, we save them here right aftre setup 
	// compeleted.
	user->save();
	ob->save();

/*.	if (user->query("gender")=="女性")
        {
          cloth = new("/obj/loginload/skirt.c");
	  cloth->move(user);
	  cloth->wear();
          cloth = new("/obj/loginload/shoes.c");
	  cloth->move(user);
	  cloth->wear();
        }
        else
        cloth = new("/obj/loginload/linen.c");
	cloth->move(user);
	cloth->wear();
*/
        if( !silent ) {
	        if(file_size(MOTD)>0)
                  user->start_more(read_file(MOTD));
		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( strlen(startroom = user->query("startroom"))<2 )
			startroom = START_ROOM;

                if(!wizardp(user) && startroom[0..2]=="/u/") {
		  startroom = START_ROOM;
                  user->set("startroom",startroom);
                }
                //added by mon 10/27/97

		// the following 7 lines are aded by snowcat dec 10 1997
		if (("/adm/daemons/band"
		    ->create_char_banned(query_ip_number(user)) == 1 ||
	    	    "/adm/daemons/band"->is_banned(query_ip_number(user))
		    == 1) && !wizardp(user)) {
			user->move("/d/wiz/guest");
			log_file( "ALLCONT", sprintf("from banned site\n"));
		}
		else if( !catch(load_object(startroom)) )
			user->move(startroom);
		else {
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		if(!wizardp(user) || !user->query("env/invisibility"))
		tell_room(startroom, user->query("name") + "连线进入这个世界。\n",
			({user}));
		
		mbx=ob->query_temp("mbox_ob");
		if (!mbx) {
		  mbx=new(MAILBOX_OB);
		  mbx->set_owner(ob->query("id"));
                }
		num=mbx->query_new_mail();
		if( num>0 ) {
	          write( GRN + "\n千里眼告诉你：有您"
		    +chinese_number(num)+
		    "封信！请到南城客栈来一趟．．．\n\n" + NOR);
		}
		destruct(mbx);
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s由%s连线进入。", user->name()+"("+capitalize(user->query("id")) + ")", query_ip_name(user)) );
	}

	UPDATE_D->check_user(user);

      {object caishen;
	if(objectp(caishen=find_object("/d/wiz/npc/caishen"))) {
	  caishen->check_one(user);
        }
      }
}

varargs void reconnect(object ob, object user, int silent)
{
        object old_link;
	
	// mon 9/15/98
	old_link=user->query_temp("link_ob");
	if(old_link && old_link!=ob)
	    destruct(old_link);

	user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
  
	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	user->reconnect();
	if( !silent && !user->query("env/invisibility")) {
		tell_room(environment(user), user->query("name") + "重新连线回到这个世界。\n",
		({user}));
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s由%s重新连线进入。", user->query("name")+"(" + capitalize(user->query("id")) + ")", query_ip_name(user)) );
	}
	UPDATE_D->check_user(user);
}

int check_legal_id(string id)
{
	int i;
	string *legalid;

	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 8 ) ) {
		write("对不起，你的英文名字必须是 3 到 8 个英文字母。\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("对不起，你的英文名字只能用英文字母。\n");
			return 0;
		}


	legalid = explode(read_file(BANNED_ID), "\n");
	for(i=0; i<sizeof(legalid); i++)   {
	   if( id == legalid[i] )   {
		  write("对不起，这种名字会造成其他人的困扰。\n");
		  return 0;
       }
	}
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);
	
	if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
		write("对不起，你的中文名字必须是一到六个中文字。\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("对不起，你的中文名字不能用控制字符。\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++) {
          ob=body[i];
	  if( clonep(ob) && getuid(ob) == name 
            && ob->query("max_gin")>0 ) return ob;
	    //check max_gin to avoid damaged user object.
        }

	return 0;
}
/*
object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++)
		if( clonep(body[i])
		&&	getuid(body[i]) == name ) return body[i];

	return 0;
}
*/
int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}
