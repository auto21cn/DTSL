
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","宽敞大路");
  set ("long", @LONG
这里是一条宽敞的大路。南边就要到扬州的北门了。有很多车马朝
南边走去，一派热闹的景象。不时有大队的官兵从你的身旁走过，吓得
路上的百姓都朝两边闪去。
LONG);

  set("exits", ([ 
 "north":__DIR__"dalu1",
 "south":__DIR__"guanlu3",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

