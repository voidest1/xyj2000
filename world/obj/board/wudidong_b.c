// cracked by vikee 2/09/2002   vikee@263.net
// wudidong_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("甯愭湰", ({ "board" }) );
        set("location", "/d/qujing/wudidong/kitchen.c");
        set("board_id", "wudidong_b");
        set("long", "杩欐槸鏃犲簳娲炵殑甯愭湰锛屾槸鍘ㄥ瓙鐢ㄦ潵璁颁笅璋佸瓭鏁簡鏂伴矞浜鸿倝鐢ㄧ殑銆俓n");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}