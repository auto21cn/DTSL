
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIG"广场"NOR);
  set ("long", @LONG
两边是龙盘的柱子，一看就是出自名家之作。皇宫戒备森严，很少
看到有人走过。
LONG);

  set("exits", ([ 
  "east":__DIR__"guangchang2",
         ]));

  set("objects",([
   __DIR__"npc/taijian1":1,
   ]));
  set("valid_startroom", 1);
  setup();
 
}

