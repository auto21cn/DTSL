
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","陡坡");
  set ("long", @LONG
这里是一个陡坡，你开始小心翼翼起来。北边就是武夷山了。从这
里可以到武夷山上。
LONG);

  set("exits", ([ 

   "northup":__DIR__"doupo1",
  "eastdown":__DIR__"doupo3",
   
          ]));
/* set("objects",([
     __DIR__"npc/youke":2,
     ]));*/
set("outdoors","wuyishan");
  
  set("valid_startroom", 1);
  setup();
 
}

