
inherit ROOM;

void create()
{
	set("short", "兵器铺");
	set("long", @LONG
这是一家兵器铺。由于连年的战火，使这里的生意很好。旁边还有
几个人在挑选挂在墙上的兵器。地上则放了很多刚刚打造好的兵器，有
钢刀、长剑等。
LONG);

	set("exits", ([
		"west" : __DIR__"nandajie2",
	]));
	set("objects",([
		__DIR__"npc/tiejiang":1,
		]));

	setup();
	replace_program(ROOM);
}

