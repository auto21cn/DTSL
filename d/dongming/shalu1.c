
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "沙路");
	set("long", @LONG
这里是一条沙路。不时有人骑着马从你的身旁驰过。这里几乎没有
什么人，一片荒凉萧瑟的气氛。
LONG);
	set("exits", ([
		"southeast":__DIR__"xiaolu2",
		"north":__DIR__"shalu2",
		]));
      set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

