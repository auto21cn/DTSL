
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short","土路");
  set ("long", @LONG
这里是一条土路。这里是陕西和河南的交界处了。从这里西行，就
可以到陕西的长安了，从这里东行，就可以到河南的洛阳了。
LONG);

  set("exits", ([ 
"northwest":__DIR__"tulu1",
"east":__DIR__"dalu1",
"northeast":__DIR__"shanlu3",
        ]));
 set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

