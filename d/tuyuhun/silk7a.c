// /d/xingxiu/silk7a.c
inherit ROOM;

void create()
{
        set("short", "人头疙瘩");
        set("long", @LONG
这里是黄黏土地带。是风蚀台地得自然景象。周围皆人迹罕至的戈
壁滩。因地处风带线上，常年多刮大风，泥土剥蚀，留下坚硬和有红柳
草根的部分，形成土墩，星罗棋布，酷似人头，故有此称。
LONG);
        set("outdoors", "tuyuhun");

        set("exits", ([
                "east" : __DIR__"silk3c",
                "northup" : __DIR__"silk7",
                "southeast" : __DIR__"silk5a",
        ]));

        setup();
//        replace_program(ROOM);
}

