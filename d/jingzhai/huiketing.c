
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIG"会客厅"NOR);
  set ("long", @LONG
这里是会客厅。这里放着几张桌子，没有什么华丽的摆设，但却不
落俗套。桌子有一层薄薄的尘埃，看来慈航静斋很久没来客人了。
LONG);

  set("exits", ([ 

  "west":__DIR__"huayuan",
       ]));
  /*set("objects",([
	  __DIR__"npc/bing":2,
	  ]));*/
  set("valid_startroom", 1);
  setup();
 
}

