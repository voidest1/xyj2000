// cracked by vikee 2/09/2002   vikee@263.net
// Room: some place in 瑗跨墰璐烘床
// cave2.c

inherit ROOM;

void create ()
{
  set ("short", "灞辨礊");
  set ("long", @LONG

蹇嶇潃棰嗕汉绐掓伅鐨勮叆姘旓紝浣犻捇杩涗竴涓礊涓紟娲炲彛铏戒笉澶э紝閲岄潰
鍗磋繕瀹芥暈锛庝絾婊″湴鐙肩睄锛屽埌澶勬槸鍔ㄧ墿楠ㄥご锛岃繕鏈変竴浜涜鎾曟垚
纰庣墖鐨勫案浣擄紟
LONG);

  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/youngwolf.c" : 2,
]));
  set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"cave1",
]));

  setup();
}