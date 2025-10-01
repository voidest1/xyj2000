// cracked by vikee 2/09/2002   vikee@263.net
// hp cmds (Mon  09-04-95)
 
#include <ansi.h>
 
inherit F_CLEAN_UP;
 
private int echo_back(string arg);

int main(object me, string arg)
{
	string ANSI_ESC = "\x1B";

	string TT   = "\x18"; // Terminal Type
	string CS   = "\x5B"; // Charset
	string MSP  = "\x5A"; // MSP
	string MXP  = "\x5B"; // MXP
	string NAWS = "\x1F"; // Negotiate About Window Size

	string IS   = "\x00"; // Negotiate About Window Size
	string SEND = "\x1F"; // Negotiate About Window Size

	string SE   = "\xF0"; // 240
	string NOP  = "\xF1"; // 241
	string DM   = "\xF2"; // 242
	string BRK  = "\xF3"; // 243
	string IP   = "\xF4"; // 244
	string AO   = "\xF5"; // 245
	string AYT  = "\xF6"; // 246
	string EC   = "\xF7"; // 247
	string EL   = "\xF8"; // 248
	string GA   = "\xF9"; // 249
	string SB   = "\xFA"; // 250
	string WILL = "\xFB"; // 251
	string WONT = "\xFC"; // 252
	string DO   = "\xFD"; // 253
	string DONT = "\xFE"; // 254
	string IAC  = "\xFF"; // 255

	if(!wizardp(me))
		return notify_fail("命令尚未开放！");

	printf("[" + "printf test" + "]" + "\n");

	// printf(IAC + WILL + MXP);
	printf(IAC + SB + MXP + "[TEST]" + IAC + SE + "\n");
	// input_to( (: echo_back :));

	return 1;
}
 
private int echo_back(string arg)
{
	int i;

	if(!arg)
		return notify_fail("Empty Reply");

	printf("[length] - %d\r\n", strlen(arg));
	printf("[ Bytes] -");
	for(i=0; i<strlen(arg); i++)
		printf(" 0x%02x", arg[i]);
	printf("\r\n");
	printf("Test Finish\r\n");

	return 1;
}

private void ex_print()
{
	string ANSI_ESC = "\x1B";

	// http://mud-dev.wikidot.com/telnet:negotiation
	// http://www.networksorcery.com/enp/protocol/telnet.htm

	// http://www.gammon.com.au/scripts/showrelnote.php?version=4.48&productid=0
	string TT   = "\x18"; // Terminal Type
	string CS   = "\x5B"; // Charset
	string MSP  = "\x5A"; // MSP
	string MXP  = "\x5B"; // MXP
	string NAWS = "\x1F"; // Negotiate About Window Size

	// From Microsoft - The Telnet Protocol
	// http://support.microsoft.com/kb/231866/en-us
	string SE   = "\xF0"; // 240
	string NOP  = "\xF1"; // 241
	string DM   = "\xF2"; // 242
	string BRK  = "\xF3"; // 243
	string IP   = "\xF4"; // 244
	string AO   = "\xF5"; // 245
	string AYT  = "\xF6"; // 246
	string EC   = "\xF7"; // 247
	string EL   = "\xF8"; // 248
	string GA   = "\xF9"; // 249
	string SB   = "\xFA"; // 250
	string WILL = "\xFB"; // 251
	string WONT = "\xFC"; // 252
	string DO   = "\xFD"; // 253
	string DONT = "\xFE"; // 254
	string IAC  = "\xFF"; // 255

	// printf(IAC + SB + MXP + IAC + SE + "\0");

	printf("<B><I><S>Test</S></I></B> This is a <a \"http://www.zuggsoft.com/\">hyperlink</a>" + "\r\n");
	printf(ANSI_ESC + "[4z<send href=\"buy water\">water" + ANSI_ESC + "[4z</send>" + "\r\n");
	/*printf(ANSI_ESC + "[31mTry MXP Command" + ANSI_ESC + "[2;37;0m" + "\r\n");
	printf(IAC + WILL + MXP + "\x0");
	printf("Test This is a <a \"http://www.zuggsoft.com/\">hyperlink</a>" + "\r\n");
	input_to( (: echo_back :) );*/

	printf(ANSI_ESC + "[4z<SEND href=\"jump\">" + "Emote Jump" + ANSI_ESC + "[4z</SEND>" + "\r\n");
	printf(ANSI_ESC + "[4z<FONT \"Microsoft YaHei\">This text is in a fancy font [中文 雅黑]" + ANSI_ESC + "[4z</FONT>" + "\r\n");
	printf(ANSI_ESC + "[4z<FONT \"SimSun\">This text is in a fancy font [中文 宋体]" + ANSI_ESC + "[4z</FONT>" + "\r\n");
	printf(ANSI_ESC + "[4z<FONT \"SimHei\">This text is in a fancy font [中文 黑体]" + ANSI_ESC + "[4z</FONT>" + "\r\n");
	printf(ANSI_ESC + "[4z<FONT \"Consolas\">[Consolas 中文 宋体]" + ANSI_ESC + "[4z</FONT>" + "\r\n");
	printf(ANSI_ESC + "[4z<FONT \"Courier New\">[Courier New 中文 宋体]" + ANSI_ESC + "[4z</FONT>" + "\r\n");
	printf(ANSI_ESC + "[4z<A href=\"http://www.zuggsoft.com\">Click here for zMUD" + ANSI_ESC + "[4z</A>" + "\r\n");
	printf(ANSI_ESC + "[4z<SEND href=\"command1|command2|command3\" hing=\"right click to see menu|Item 1|Item 2|Item 2\">this is a menu link (right click)" + ANSI_ESC + "[4z</SEND>" + "\r\n");
	printf(ANSI_ESC + "[4z<IMAGE fname=\"937c08579bd03c48bf259c24104ba4f6.jpg\" url=\"http://baike.baidu.com/cms/rc/r/image/2013-07-24/\">"+"\r\n");

	//printf(ANSI_ESC + "[4z<IMAGE fname=\"6aa09e8fgw1e6z3eoeexpg209g05bu0x.gif\" url=\"http://ww2.sinaimg.cn/large/\">"+"\r\n");
	//printf(ANSI_ESC + "[1z<VERSION>"+"\r\n");
	//printf(ANSI_ESC + "[4z<FRAME Name=\"Map\" Width=\"20c\" INTERNAL align=\"right\">" + "\r\n");
}

int help(object me)
{
	write(@HELP
指令格式 : wow
 
这个指令可以进入 WoW ~ ~ ~
 
HELP
    );
    return 1;
}
