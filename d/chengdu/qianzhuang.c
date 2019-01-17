
inherit ROOM;

void create()
{
	set("short", "钱庄");
	set("long", @LONG
这是成都的一家有名的钱庄。这里的信誉很好，但是由于连年的兵
荒马乱，来存钱的人也就不多了。老板正在柜台处敲打算盘，几个伙计
闲来无事，有的在聊天，有的趴在桌子上打着呵欠。打着呵欠。
LONG
	);
	set("exits", ([
		"north" : __DIR__"xidajie2",
	]));
	set("objects",([
		__DIR__"npc/zhang":1,
		]));
	setup();
	replace_program(ROOM);
}

