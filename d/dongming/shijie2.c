
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", GRN"石阶"NOR);
	set("long", @LONG
这里是一级级的向上的石阶。清风徐徐吹来，你感到一阵的清爽。
这里种了很多鲜花。两边还种了很多青竹。
LONG);
	set("exits", ([
	     
		"southup" :__DIR__"shijie3",
		"northdown":__DIR__"shijie1",
		
	]));
	
        
       set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

