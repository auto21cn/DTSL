
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","官路");
  set ("long", @LONG
这里是一条官路。南边就是成都了。这里的行人渐渐多了起来，远
处传来热闹的声音。
LONG);

  set("exits", ([ 
  "northeast":__DIR__"shashilu2",
  "southwest":__DIR__"guanlu4",
         ]));
set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

