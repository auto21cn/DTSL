
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","山谷");
	set("long", @LONG
这是一个寂静的山谷，风景秀丽，鸟语花香。清风吹来，可以听到
绿草沙沙的声音，闻到阵阵的花香。这里地势偏僻，看起来很久没人来
过了。
LONG);
        set("exits",([          
          "down":__DIR__"xiaoxi",
          ]));
        
	setup();      
}
