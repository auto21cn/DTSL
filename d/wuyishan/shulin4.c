
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","树林");
  set ("long", @LONG
这里是一片树林。这里非常阴暗，你不禁小心起来。北边有一条小
溪。东边是一个陡坡。
LONG);

  set("exits", ([ 

   "north":__DIR__"xiaoxi2",
   "east":__DIR__"doupo1",
 
          ]));
  set("objects",([
     "/d/dongming/obj/shibei":1,
     ]));
set("outdoors","wuyishan");
  
  set("valid_startroom", 1);
  setup();
 
}

