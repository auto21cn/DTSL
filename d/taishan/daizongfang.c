
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","岱宗坊");
  set ("long", @LONG
这里是泰山的岱宗坊。从这里上去，就可以到泰山的南天门了。有
很多游人从你身旁走过。抬头望去，泰山高耸的山峰已经深入云端。
LONG);

  set("exits", ([ 

   "up":__DIR__"baihequan",
   "northup":__DIR__"wshandao1",
   "east":"/d/yangzhoubei/taishanjiao",
   //"south":"/d/leshou/eroad3",
          ]));
 set("objects",([
     __DIR__"npc/youke":2,
     ]));
set("outdoors","taishan");
  
  set("valid_startroom", 1);
  setup();
 
}

