
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","石铺通路");
  set ("long", @LONG
这里是一个石铺通路。两旁植有苍松翠柏，房舍藏在林木之间。景
色幽深，气氛淡雅。
LONG);

  set("exits", ([ 
  
	  "southwest":__DIR__"qiao",
	  "north":__DIR__"paifang",
         ]));
 set("outdoors","chengdu");
  set("valid_startroom", 1);
  setup();
 
}
