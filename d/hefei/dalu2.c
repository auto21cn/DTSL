
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","大路");
  set ("long", @LONG
这里是条宽敞的大路。这里可以望见襄阳的城墙了。西边是条官路。
这里的行人已经很多了。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"dalu1",
  "southwest":"/d/xiangyang/guanlu2",
       ]));
 
set("outdoors","hefei");
  
  set("valid_startroom", 1);
  setup();
 
}

