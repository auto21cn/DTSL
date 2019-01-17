
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
这里是一条小路，南边就是安徽和江苏的交界了。这里的行人不是
很多。不时有人骑着马从你的身旁驰过。
LONG);

  set("exits", ([ 
 "northwest":__DIR__"xiaolu2",
 "southeast":__DIR__"xiaolu4",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

