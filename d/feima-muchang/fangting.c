
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"方亭"NOR);
  set ("long", @LONG
这里是一座方亭，前临百丈高崖，对崖一道瀑布飞泻而下，气势迫
人，若非受竹林所隔，院落处必可听到轰鸣如雷的水瀑声。
LONG);

  set("exits", ([ 

	  "west":__DIR__"zhulin",
	  "southeast":__DIR__"xiaolu5",
  ]));

  
  set("valid_startroom", 1);
  setup();
 
}

