
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
这里是一条小路。这里已经是安徽的境地了。这里并不象刚才那么
繁华。行人不是很多。
LONG);

  set("exits", ([ 
 "northeast":"/d/jiujiang/dalu1",
 "southeast":__DIR__"guanlu2",
 "southwest":"/d/jiujiang/shalu3",
 "westup":__DIR__"xiaolu2",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

