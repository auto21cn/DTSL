
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小径");
  set ("long", @LONG
这里是一条幽静的小径。西面是阴癸派长老边不负的卧室了。平时
很少有人来这里。只有打扫卧室的弟子从这里经过。
LONG);
  set("exits",([
	  "west":__DIR__"woshi1",
	  "south":__DIR__"caodi",
	  ]));

  set("outdoors","yinkui");

  set("valid_startroom", 1);
  setup();
 
}

