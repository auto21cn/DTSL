
#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short",HIW"巫师会议室"NOR);
  set ("long", @LONG
这里是巫师聊天的地方。这里有一个留言板，上面有巫师的留言。
这里放着五十两黄金和五十两白银。
LONG);

  set("exits", ([ 
 "east":__DIR__"wizroom",
 "north":__DIR__"wizroom5",
 "west":__DIR__"qc",
        ]));
  set("objects",([
 "/u/yanyan/box":1,
    ]));
  set("valid_startroom", 1);
  setup();
  call_other("/obj/board/wiz_b", "???"); 
  
}


