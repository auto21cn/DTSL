
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安化门");
  set ("long", @LONG
这是长安城的安化门，城墙上贴着几张官府告示。官兵们警惕地注
视着过往行人，你最好小心为妙。一条笔直的青石板大道向北延伸。
LONG);

  set("exits", ([ 
 "east":__DIR__"xiaolu9",
 "north":__DIR__"xpdajie3",
        ]));
  set("objects",([
	  __DIR__"npc/bing":2,
	  ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

