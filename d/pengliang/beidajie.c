inherit ROOM;

void create()
{
	set("short", "北大街");
	set("long", @LONG
这是一条宽阔的青石街道，向南北两头延伸。东边是一茶馆，一面
上书“茶”的招幡在风中轻轻地摇曳着，一股股茶香扑面而来。西面是
梁都的兵营，隐隐能听见里面传来的操练声。
LONG );
        set("outdoors", "pengliang");
	set("no_clean_up", 0);

	set("exits", ([
		"east"  : __DIR__"chaguan",
		"south" : __DIR__"shizijietou",
		"west"  : __DIR__"junying",
		"north" : __DIR__"beimen",
	]));
	setup();
	replace_program(ROOM);
}

