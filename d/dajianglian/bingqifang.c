
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short","兵器房");
  set ("long", @LONG
这里是兵器房。这里横七竖八地放着各种兵器，由于战乱，所以大
江联每个弟子都处于备战状态。
LONG);

  set("exits", ([ 
	  "west":__DIR__"tulu1",
	      ]));
  set("objects",([
	  __DIR__"obj/changjian":2,
	  __DIR__"obj/blade":2,
	  ]));
  set("valid_startroom", 1);
  setup();
 
}

