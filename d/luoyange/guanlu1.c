
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","官路");
  set ("long", @LONG
这里是洛阳的东门的官路。往东走可以到达堰师。这里的行人很多，
但主要还是武林人士。
LONG);

  set("exits", ([ 
  "west":"/d/luoyang/dongmen",
  "southeast":__DIR__"guanlu2",
        ]));
 set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

