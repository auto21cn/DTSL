
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","商馆");
  set ("long", @LONG
这里是商馆，各地的商旅来往行商居住的地方。
LONG);

  set("exits", ([ 
      "west":__DIR__"qinglongjie3",
  ]));
  set("valid_startroom", 1);
  set("no_fight",1);
  setup();
 
}

