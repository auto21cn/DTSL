
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","商馆");
  set ("long", @LONG
这里是商馆，各地的商旅来往行商居住的地方。
LONG);

  set("exits", ([ 
      "west":__DIR__"qinglongjie2",
  ]));
  set("valid_startroom", 1);
  setup();
 
}