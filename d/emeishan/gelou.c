
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","阁楼");
  set ("long", @LONG
这里是峨嵋山的一座阁楼。此阁位于牛心岭下，东有白龙江，西有
黑龙江，两江之水交汇于清音阁下。
LONG);

  set("exits", ([ 
 "eastdown":__DIR__"jingxinan",
      ]));
 set("valid_startroom", 1);
  setup();
 
}

