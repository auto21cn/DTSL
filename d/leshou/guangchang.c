// /d/zhuojun/guangchang.c
// Room in 涿郡
// laowuwu 99/04/11
inherit ROOM;
void create()	
{
	set("short", "中心广场");
        set("long", @LONG
这里是位于乐寿城的中心的中心广场，一座钟楼高耸在中心广场的
中央，西面就是乐寿城好色客留恋忘返的胭脂巷，南，北，东三条大道
各通向乐寿的各个城门。
LONG
	);
set("outdoors", "/d/zhuojun");
set("exits", ([
		"north" :__DIR__"beidajie2",
                "south"  :__DIR__"nandajie2",
                "west"  :__DIR__"yanzixiang",
                 "east"  :__DIR__"dongdajie2",
	]));
	set("objects",([
	  __DIR__"npc/bing":1,
	  ]));
       setup();
	replace_program(ROOM);
}	
