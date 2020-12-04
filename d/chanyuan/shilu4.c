
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","石路");
  set ("long", @LONG
这里是净念禅院的石路。往东走就是禅院的后门了。这里没有什么
人，几乎没有人来这里。阵阵梵呗诵经之声，悠悠扬扬的似从遥不可知
的远处传来，传遍寺院。
LONG);

  set("exits", ([ 
	  "east":__DIR__"shilu5",
	  "west":__DIR__"tongdian",
  
         ]));

  set("outdoors","chanyuan");
  set("valid_startroom", 1);
  setup();
 
}

