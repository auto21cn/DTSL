
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","山路");
  set ("long", @LONG
这里是一条山路。抬头望去，北边就是一座庙宇。庙宇看起来不是
很大，但在这种氛围中，显得超凡脱俗一般。
LONG);

  set("exits", ([ 
 "down":__DIR__"shanlu4",
 "northup":"/d/jingzhai/door",
         ]));
  set("outdoors","cbs");
  
  set("valid_startroom", 1);
  setup();
 
}

