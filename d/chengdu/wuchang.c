
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","练武场");
  set ("long", @LONG
这里是个练武场。独尊堡的弟子平时就在这里练习武艺。只听这里
呼喝练武的声音不绝。几个弟子正努力地习武，顿时整个练武场尘土飞
扬。
LONG);

  set("exits", ([ 
	  "north":__DIR__"xiuxishi",
	  "south":__DIR__"caodi4",
	  "east":__DIR__"bingqishi",
        ]));
  set("objects",([
	  __DIR__"npc/dizi3":1,
	  ]));
 set("outdoors","chengdu");
  set("valid_startroom", 1);
  setup();
 
}
