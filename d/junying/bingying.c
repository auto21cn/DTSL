// Room: /d/junying/bingying.c

inherit ROOM;

void create()
{
	set("short", "兵营");
	set("long", @LONG
这里是兵营。兵营里静寂寂的，除了巡逻兵外。没什么人了。营盘里刀
枪摆放整齐。一人多高的栅栏把营盘包在当中。你走进当中，似乎有些迷路
，你隐隐感到一种玄机，一股杀气暗藏其中。你突然发现一队巡逻兵正监视
着你，你不禁暗暗盘算，还是赶快离开为妙。
LONG
	);
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/xunluo" : 1,
]));
	set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"showroom",
  "south" : "/d/huating/junying",
  "north" : __DIR__"wqgate",
]));

	setup();
	replace_program(ROOM);
}
