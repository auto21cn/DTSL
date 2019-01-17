
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
这是玄武门外的青石大路，道路宽敞而干净，汉白玉砌的路面被雨
水冲得光明如镜，道路两旁载着参天的古木，听到树上的小鸟时而不时
的啾鸣几声，这里到处都散发着安祥宁静的气氛。从这里向东是东宫的
后门，向西则是掖庭宫的后门。
LONG);

  set("exits", ([ 
 "north":__DIR__"xineiyuan",
 "south":__DIR__"xuanwumen",
 "west":__DIR__"qingshilu1",
 "east":__DIR__"qingshilu3",
        ]));
 

  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

