
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","草地");
  set ("long", @LONG
这里是片草地。北面是石林了。这里空气清新，看着周围的景色，
听着鸟儿的鸣叫声，你觉得舒服极了。
LONG);

  set("exits", ([ 
 "north":__DIR__"shilin",
 "southwest":__DIR__"xiaojing2",
       ]));
   set("outdoors","emeishan");
 set("valid_startroom", 1);
  setup();
 
}

