
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","望仙大街");
  set ("long", @LONG
这是望仙大街，南北贯通长安城。大街上十分热闹，人来人往川流
不息。东面有一座很大的寺庙，那里就是长安最大的寺院东大寺。
LONG);

  set("exits", ([ 
 "north":__DIR__"wxdajie3",
 "south":__DIR__"gmdajie2",
 "east":__DIR__"dongdasi",
        ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

