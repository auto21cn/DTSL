
#include <ansi.h>

inherit ROOM;

#define SHIPDIR __DIR__"ship"
#define FROM __DIR__"dukou2"
#define TO __DIR__"dukou1"

#include "/std/shiproom.c"

void create ()
{
  set ("short","黄河渡口");
  set ("long", @LONG
这里是黄河西岸的渡口。面前是滚滚的黄河，只有几个艄公在这里
摆渡来往的行人。
LONG);

  set("exits", ([ 

  "west":__DIR__"road8",
         ]));
set("outdoors","taiyuan");
  set("valid_startroom", 1);
  setup();
 
}

