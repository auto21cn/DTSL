
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","卧室");
  set ("long", @LONG
这里是解文龙的卧室了。床上的被褥叠得很整齐。旁边的桌子上整
齐地放着文房四宝。这里看来很整洁，似乎是刚刚打扫过。不时有丫鬟
从这里进进出出。
LONG);

  set("exits", ([ 
  
	  "north":__DIR__"changlang2",
       ]));
  set("objects",([
	  __DIR__"npc/xiewenlong":1,
	  ]));
  set("valid_startroom", 1);
  setup();
 
}
