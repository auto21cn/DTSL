
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","树林");
  set ("long", @LONG
这里是一片茂密的树林，阳光零散地从你的头上射了下来，鸟鸣声
不绝于耳。西边是一条山路。这片树林看起来很大，估计要走一会才能
出去。
LONG);

  set("exits", ([ 

   "west":__DIR__"shanlu2",
   "east":__DIR__"shulin3",
  
          ]));
/* set("objects",([
     __DIR__"npc/youke":2,
     ]));*/
set("outdoors","wuyishan");
  
  set("valid_startroom", 1);
  setup();
 
}

