
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
这里是条小路。很多商旅为了避免事故，所以乘船从洛阳去堰师。
这里风景秀丽，山水如画，空气清新。地上有很多漂亮的野花、蒲公英
等植物。不时有野兔从你的脚旁跳过。
LONG);

  set("exits", ([ 
  "west":__DIR__"xiaolu1",
  "northeast":__DIR__"xiaolu3",
        ]));
 set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

