
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short",HIG"聚义堂"NOR);
  set ("long", @LONG
这里是大江联分舵的聚义堂。正上方悬挂着一个大牌子，上面工工
整整地写着三个大字：聚义堂。这里庄严肃穆，你不禁放低了脚步。
LONG);

  set("exits", ([ 
	  "east":__DIR__"shilu",
	     ]));
  set("objects",([
	  __DIR__"npc/mengzhu":1,
	  ]));
set("no_clean_up",1);
  set("valid_startroom", 1);
  setup();
 
}

