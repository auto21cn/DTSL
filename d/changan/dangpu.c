
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","荣达大押");
  set ("long", @LONG
这家当铺据说是平窑富商欧阳福荣在长安开的分号，欧阳福荣靠典
当起家，富甲一方。分号老板冷冷地站在柜台后，对来典卖东西的人向
来毫不留情。有几个人站在那里，正在犹豫是否典卖手里的东西。
LONG);

  set("exits", ([ 
 "west":__DIR__"qydajie4",
        ]));
  set("objects",([
	  __DIR__"npc/tie":1,
	  ]));
  
  set("valid_startroom", 1);
  setup();
 
}

