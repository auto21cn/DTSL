
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", GRN"休息室"NOR);
	set("long", @LONG
这里是东溟派的休息室。床上放着几个被褥，有几个东溟派弟子正
在那里熟睡，打着轻鼾。你来到这里，不禁有些困了。
LONG);
	set("exits", ([		
		"west":__DIR__"tingyuan",		
	]));
      set("sleep_room",1);
        
       set("valid_startroom", 1);   
     
	setup();
       
       
}

