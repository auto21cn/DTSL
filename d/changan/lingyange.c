

#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","凌烟阁");
  set ("long", @LONG
这里的长安的胜地凌烟阁。从这里看去，下面的景色尽收眼底。这
里的摆设清雅脱俗，给人一种舒服的感觉。
LONG);

  set("exits", ([ 
 "west":__DIR__"dongshidongjie3",
 
        ]));
  set("objects",([
    "/d/quest/yrs/huashi":1,
    ]));
  set("valid_startroom", 1);
  setup();
 
}

