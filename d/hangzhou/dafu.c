
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","大富之家");
  set ("long", @LONG
这里是一个大富之家。据说这家的主人李财主是杭州的首富，他的
女儿近日要举行比武招亲，吸引了不少武林人士。
LONG);

  set("exits", ([ 

  "east":__DIR__"nandajie1",
  "enter":__DIR__"tingyuan",
      ]));

set("outdoors","hangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

