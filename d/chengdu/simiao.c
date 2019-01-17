
inherit ROOM;

void create()
{
	set("short", "大石寺");
	set("long", @LONG
这是成都的一座寺庙，平时有很多人来这里进香拜佛。如今战乱年
代，没有多少人来烧香了。院子的中央是一个大香炉，如今已经十分冰
冷，很久没有香火了。两边是几间破旧的厢房，看来已经很久没有人居
住了。
LONG);
        set("outdoors", "成都");

	set("exits", ([
		"north":__DIR__"xidajie1",
		"enter":__DIR__"dadian",
	]));

	setup();
	replace_program(ROOM);
}

