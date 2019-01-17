
#include <room.h>

inherit ROOM;
void create()
{
	set("short", "许城南门");
	set("long", @LONG
这是南城门，城门正上方刻得有个大大的＂魏＂字。城墙上贴着几
张官府告示。一条大路往南通向彭梁。
LONG );
	set("exits", ([
		"south" : __DIR__"dadao9",
		"north" : __DIR__"houqiang",
	]));
	set("objects", ([
		__DIR__"npc/bing" : 2,
		__DIR__"npc/wujiang":1,
	]));
	set("outdoors", "xucheng");
	setup();
	replace_program(ROOM);
}

