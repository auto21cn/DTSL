
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","草地");
  set ("long", @LONG
这里是一片草地。西面就是飞马牧场的菜园了。有几个飞马牧场的
弟子正在朝那里走去，看来是去菜园种菜干活的。
LONG);

  set("exits", ([ 
	  "west":__DIR__"caiyuan",
	  "east":__DIR__"qingshilu3",
    ]));

  set("outdoors","feima");
  set("valid_startroom", 1);
  setup();
 
}

