
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","通远大街");
  set ("long", @LONG
你走在通远大街上，这条大街横贯长安城东西，东连通化门，西至
开远门，是长安城的主干道之一。南北通向的大街是安化大街，北面是
芳林门。
LONG);

  set("exits", ([
 "north":__DIR__"fanglinmen",
 "south":__DIR__"ahdajie5",
 "east":__DIR__"tydajie4",
 "west":__DIR__"tydajie2",
        ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

