
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short","沙路");
  set ("long", @LONG
这里是一条沙路。由于连年的战乱，时有累累白骨散落于荒凉的野
外。烈日炎炎下，毫无生气，偶尔有盘旋于空中的秃鹫俯身冲下，贪婪
地争抢剩下的腐肉。
LONG);

  set("exits", ([ 
"northwest":__DIR__"shalu1",
"southeast":__DIR__"lguanlu1",
       ]));
 set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

