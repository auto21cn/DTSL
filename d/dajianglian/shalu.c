
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short","沙路");
  set ("long", @LONG
这里是一条沙路。这里的人很少，四周非常寂静。再往东边走，就
是分舵的休息室了。
LONG);

  set("exits", ([ 
	  "west":__DIR__"shilu",
	  "east":__DIR__"xiuxishi",
	     ]));
set("outdoors","dajiang");
  /*set("objects",([
	  __DIR__"npc/dizi":2,
	  ]));*/
  set("valid_startroom", 1);
  setup();
 
}

