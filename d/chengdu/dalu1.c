

inherit ROOM;

void create()
{
	set("short", "大路");
	set("long", @LONG
这是一条大路。东边是成都的北大街。西边是成都的万岁湖。那里
是成都独尊堡的地方了。
LONG);
        set("outdoors", "成都");

	set("exits", ([
		"east":__DIR__"beidajie4",
		"west":__DIR__"wansuihu",
		
	]));

	setup();
	replace_program(ROOM);
}

