#include <ansi.h>
inherit ROOM;
 void create()
{
       set("short", "柴房");
       set("long", @LONG
这里是李财主家的柴房。地上放着很多刚劈好的木柴和几把柴刀。
平时有人在这里干活。这里光线阴暗，空气非常浑浊。
LONG);
    
       set("exits", ([
               "east" : __DIR__"tingyuan",
			            
       ]));
	
       setup(); 
      
}

