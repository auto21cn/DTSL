inherit ROOM;
void create()
{
	set("short", "军营");
	set("long", @LONG
这里是黎阳守军的驻地，在黎阳城东，军营占地面积庞大，北面是
营房，南面是小校场，西面紧挨着城墙是一排马厩。
LONG );
	set("exits", ([
		"south" : __DIR__"xiaojiaochang",
		"north" : __DIR__"yingfang",
		"west"  : __DIR__"qingshilu",
		"east"  : __DIR__"malan",
	]));
	set("objects", ([
		__DIR__"npc/bing" :2,
	]));
	set("outdoors", "liyang");
	setup();
	replace_program(ROOM);
}

