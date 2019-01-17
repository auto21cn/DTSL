
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","长廊");
  set ("long", @LONG
这里是一道长廊。长廊的左右种了各种奇花异草，美不胜收。花草
的品种繁多，色彩艳丽，美不胜收。只看这里花草的品种，就可以看出
宋家堡财富的富足。
LONG);

  set("exits", ([ 

  "north":__DIR__"changlang1",
  "south":__DIR__"zhengting",
        ]));
  set("objects",([
	  __DIR__"npc/songbang":1,
	  ]));
  set("valid_startroom", 1);
  set("outdoors","lingnan");
  setup();
 
}

