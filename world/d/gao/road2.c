// cracked by vikee 2/09/2002   vikee@263.net
// gate.c

inherit ROOM;

void create()
{
  set ("short", "琛楅亾");
  set ("long", @LONG

鍛ㄥ洿鏈変竴浜涘簵閾猴紝搴楀涓轰簡鎶㈢敓鎰忥紝鎶婁笢瑗块兘鎽嗗埌浜嗚涓婏紟鎶婁竴
鏉℃湰鏉ュ氨涓嶅鐨勭煶琛楀崰浜嗗ぇ鍗婏紟杩欓噷鐨勪汉涔熸樉鐨勮緝澶氾紝澶у鏄簺
涔′笅鏉ョ殑锛屾潵涔颁笂浜涙棩甯哥敤鍝侊紟
LONG);
set("exits", ([ /* sizeof() == 4 */
"north" : __DIR__"budian",
"south": __DIR__"tiepu",
"east" : __DIR__"road1",
"west" :__DIR__"road3",
]));

        set("outdoors", 1);
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}


