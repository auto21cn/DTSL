
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","官路");
  set ("long", @LONG
这里是条官路。西北面就是洛阳城了，这里的行人不是很多。来来
往往的大多是武林人士。
LONG);

  set("exits", ([ 
 "northwest":__DIR__"guanlu1",
 "southeast":__DIR__"shalu1",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

