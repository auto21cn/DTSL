
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","小山包");
  set ("long", @LONG
这里是一个光突突的小山包，除了半山坡的几棵小树外，几乎没有
任何的植物，所以根本也就看不见什么动物。
LONG);

  set("exits", ([ 
 "northdown":__DIR__"shanlu1",
         ]));

set("outdoors","hefei");
  
  set("valid_startroom", 1);
  setup();
 
}
