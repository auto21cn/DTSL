
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","宜春院");
  set ("long", @LONG
这里是太子李建成接待一般宾客的地方，环境清雅，景致极佳，门
外是人工湖经绪池，水光澈滟、渔沉荷浮，湖旁花树罗列，一道长桥跨
湖而过，至湖心置一六角亨，通抵院门。
LONG);

  set("exits", ([ 
 "west":__DIR__"xiandemen",
         ]));
  set("valid_startroom", 1);
  setup();
 
}

