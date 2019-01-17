
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
这里是条小路。这里已经没有什么人来了。北边有一个柴房，里面
传来了阵阵锯木头的声音。西边是禅院的武场，呼喝的声音不时传来。
阵阵梵呗诵经之声，悠悠扬扬的似从遥不可知的远处传来，传遍寺院。
LONG);

  set("exits", ([ 
      "northeast":__DIR__"chaifang",
	  "west":__DIR__"wuchang",
      ]));

  set("outdoors","chanyuan");
  set("valid_startroom", 1);
  setup();
 
}

