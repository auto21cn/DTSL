
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","山路");
  set ("long", @LONG
这里是山路。从这里向上攀登，就可以到泰山的顶部了。这里的山
路非常狭窄，崎岖曲折，非常难走。游人一般都是排队向上攀登。
LONG);

  set("exits", ([ 

   "westdown":__DIR__"baihequan",
   "westup":__DIR__"shanlu2",
          ]));
 /*set("objects",([
     __DIR__"npc/youke":2,
     ]));*/
set("outdoors","taishan");
  
  set("valid_startroom", 1);
  setup();
 
}

