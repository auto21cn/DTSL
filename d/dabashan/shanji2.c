
#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short","山脊");
  set ("long", @LONG
这里是一个山脊。这里地势陡峭，一不小心，就会摔到下面的万丈
深崖。东边是个小山坡，西边是条下山的路。
LONG);

  set("exits", ([ 

   "eastdown":__DIR__"shanpo",
   "westdown":__DIR__"shanlu5",
           ]));

set("outdoors","dabashan");
  
  set("valid_startroom", 1);
  setup();
 
}
