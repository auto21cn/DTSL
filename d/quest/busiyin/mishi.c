
inherit ROOM;
#include <ansi.h>

void create()	
{
	set("short",HIB"密室"NOR);
	set("long", @LONG
这里是一个密室。上面有一个出口。这里黑洞洞的，什么也看不清
楚。
LONG);
    set("exits", ([
	        "up" : __DIR__"woshi",
	]));
   set("objects",([
      __DIR__"obj/mask":1,
      ]));
 	  setup();
	
}

