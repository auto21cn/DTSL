
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","草地");
  set ("long", @LONG
这里是片草地。这里没有什么装饰，但显得有些庄严的气氛，似乎
是南边的小屋传来的杀气。
LONG);

  set("exits", ([ 

   "northwest":__DIR__"yuedongmen",
   "southeast":__DIR__"modaotang",
        ]));
  set("objects",([
	  "/d/clone/npc/ouyangqian":1,
	  ]));
  set("valid_startroom", 1);
  set("outdoors","lingnan");
  setup();
 
}

