
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIW"大唐双龙QC场"NOR);
  set ("long", @LONG
这里是大唐双龙的QC场，用来进行QC的地方。巫师可以在这 CLONE
东西来测试。
LONG);

  set("exits", ([ 
 "east":__DIR__"wizroom2",
        ]));

  set("valid_startroom", 1);
  setup();
 
 "/obj/board/all_post_b.c"->foo();
}


