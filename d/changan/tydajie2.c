
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","通远大街");
  set ("long", @LONG
你走在通远大街上，这条大街横贯长安城东西，东连通化门，西至
开远门，是长安城的主干道之一。南北通向的大街是永安大街，北面是
景耀门。
LONG);

  set("exits", ([
 "north":__DIR__"jingyaomen",
 "south":__DIR__"yadajie3",
 "westup":__DIR__"tyqiao",
 "east":__DIR__"tydajie3",
        ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

