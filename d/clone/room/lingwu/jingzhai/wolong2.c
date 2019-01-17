
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","望天角");
  set ("long", @LONG
这里就是卧龙岭上的望天角。这里地势狭窄，好似一条飞龙的龙角。
从这里可以看到山下的皑皑白雪，一阵寒风吹来，卷起阵阵风雪。两旁
均是峭壁陡崖，一不小心就会滑落下去。
LONG);

  set("exits", ([ 
 "westdown":__DIR__"wolong1",
 "northup":__DIR__"wolong3",
 "eastup":__DIR__"wolong5",
        ]));
  set("outdoors","wolongling");
  
  set("valid_startroom", 1);
  setup();
 
}

