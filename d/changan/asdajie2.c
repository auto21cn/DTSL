
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","安上大街");
  set ("long", @LONG
这是安上大街，南北连接长安城的兴平街和建福门。这条街是长安
的南北向主要大街，长安皇城就在安上北街的西面。街上十分热闹，人
来人往川流不息。
LONG);

  set("exits", ([ 
 "north":__DIR__"asdajie3",
 "south":__DIR__"asdajie1",
        ]));
  set("outdoors","changan");
  set("valid_startroom", 1);
  setup();
}

