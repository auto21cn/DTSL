
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","小桥");
  set ("long", @LONG
这里是个小桥。南边是一个竹林。桥下有很多鱼儿游来游去。有几
个宋家堡的弟子正在桥上休息，悠闲地看着桥下水中的游鱼。不时有几
名弟子从你的身旁走过。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"huayuan1",
 "southwest":__DIR__"zhulin",
       ]));

  set("valid_startroom", 1);
  set("outdoors","lingnan");
  setup();
 
}

