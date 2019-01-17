
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","石板路");
  set ("long", @LONG
这是一条清幽的石板小路，两旁是高高的坊院墙，走在石板路上，
脚下传来“搭－搭”的声音。
LONG);

  set("exits", ([ 
 "north":__DIR__"xuanpingfang",
 "west":__DIR__"duoqingwo",
        ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

