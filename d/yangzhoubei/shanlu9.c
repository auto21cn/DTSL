
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","山路");
  set ("long", @LONG
这里是条山路。远处有一座山，好象就是有名的长白山。天气有些
冷，加上周围的景象，你不禁产生一股凄凉的感觉。
LONG);

  set("exits", ([ 
 "southeast":__DIR__"shanlu10",
 "west":__DIR__"shanlu8",
        ]));
  set("outdoors","yangzhoubei");
  
  set("valid_startroom", 1);
  setup();
 
}

