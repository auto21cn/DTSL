
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIW"文智堂"NOR);
  set ("long", @LONG
这里是慈航静斋的文智堂。这里是慈航静斋弟子学习文化的地方。
这里放着几张桌子，上面放着纸张和笔。
LONG);

  set("exits", ([ 

  "east":__DIR__"pushantang",
  "west":__DIR__"cangjingfang",
    ]));
  set("objects",([
	  __DIR__"npc/qinwenxin":1,
	  ]));

  
  set("valid_startroom", 1);
  setup();
 
}

