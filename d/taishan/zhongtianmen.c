
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","中天门");
  set ("long", @LONG
这里是泰山的中天门。来到这里，攀登泰山的路程就已经走了一半
了。望着泰山的顶峰，一股豪壮的气势不觉油然而生。
LONG);

  set("exits", ([ 

   "northup":__DIR__"yunbuqiao",
   "westdown":__DIR__"hutiange",
          ]));

set("outdoors","taishan");
  
  set("valid_startroom", 1);
  setup();
 
}

