
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","竹林");
  set ("long", @LONG
这里是个竹林。碧竹节节，随风轻摆。东边是货物房。再往南走就
是后堡了。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"xiaoqiao1",
 "east":__DIR__"huowufang",
 "south":__DIR__"houbao",
       ]));

  set("valid_startroom", 1);
  set("outdoors","lingnan");
  setup();
 
}

