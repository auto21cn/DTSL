
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","山冈");
  set ("long", @LONG
这里是山冈。从这里可以遥遥望见洛阳城了。这里几乎没有什么人，
一片荒凉萧瑟的气氛。四周杂草丛生，只有几只野兔不时从你的脚前跑过。
LONG);

  set("exits", ([ 
 "west":__DIR__"shashilu3",
       ]));
  set("outdoors","xiangyang");
  
  set("valid_startroom", 1);
  setup();
 
}

