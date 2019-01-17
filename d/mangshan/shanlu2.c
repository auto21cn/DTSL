
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","山路");
  set ("long", @LONG
这里是条山路，这条路是通往邙山的。四周树木茂盛，远处秀丽的
风景映入眼帘，四周四周丛林密布，鲜花绿草若隐若现，不时有鸟儿从
你的头上飞过。据说山上座「老君观」。
LONG);

  set("exits", ([ 

  "southwest":__DIR__"shanlu1",
 "eastup":__DIR__"shanlu3",
         ]));

  set("valid_startroom", 1);
  setup();
 
}

