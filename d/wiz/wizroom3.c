
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIW"巫师会议厅2"NOR);
  set ("long", @LONG
这里是巫师会议厅 2，这里放着大唐双龙的排行榜。请巫师不要随
便get。
LONG);

  set("exits", ([ 
 "south":__DIR__"wizroom",
        ]));

  set("valid_startroom", 1);
  setup();
  "/obj/tboard/topc_b.c"->foo();
}


