
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西市东口");
  set ("long", @LONG
这里就是位于永安大街上的闻名长安的西市－利人市的东口，路口
向西，就能走到热闹非凡的西市。
LONG);

  set("exits", ([ 
 "north":__DIR__"gmdajie6",
 "south":__DIR__"xishidongkou2",
 "westup":__DIR__"fyqiao",
         ]));
  
  set("outdoors","changan");
  set("valid_startroom", 1);
  setup();
 
}

