
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"走廊"NOR);
  set ("long", @LONG
这里是王府的走廊。四周非常寂静，不时有丫鬟从这里走过。墙壁
上有很多壁画，多是山水风景，手笔不凡。几个巡逻的侍卫用威严的眼
光打量着来往的人。
LONG);

  set("exits", ([ 

  "west":__DIR__"wangfu_neiting",
  "north":__DIR__"shufang",
  "east":__DIR__"caizheng_ting",
       ]));
  

  
  set("valid_startroom", 1);
  setup();
 
}

