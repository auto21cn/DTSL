// /d/gaoli/dongdajie1
// Room in 山海关
// rich 99/04/05
inherit ROOM;
void create()	
{
	set("short", "东大街");
	set("long", @LONG
这里的路相当的宽，能容好几匹马车并行，地面都是由青石铺成，
正对面是塞漠帮的堂口，北面是山海关的盐局，南面传来大小的吆和声。
LONG
	);
set("outdoors", "/d/shanhaiguan");
set("exits", ([
		"north" : __DIR__"yanju",
		"south" : __DIR__"duchang",
                "east" : __DIR__"saimobang",  
                "west" : __DIR__"guangchang",        
	]));
     set("objects",([
        __DIR__"npc/man":1,
        ]));
       setup();
	replace_program(ROOM);
}	
