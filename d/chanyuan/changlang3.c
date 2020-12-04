
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","长廊");
  set ("long", @LONG
这里是净念禅院的长廊。墙壁上画着很多佛像，看上去栩栩如生。
一看就是出自著名的工匠之手。阵阵梵呗诵经之声，悠悠扬扬的似从遥
不可知的远处传来，传遍寺院。
LONG);

  set("exits", ([ 
	  "enter":__DIR__"cangjing-fang",
	  "south":__DIR__"changlang2",
	  "westdown":__DIR__"caodi1",
	  "eastdown":__DIR__"caodi2",
         ]));

  
  set("valid_startroom", 1);
  setup();
 
}

