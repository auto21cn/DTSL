
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","海滨");
  set ("long", @LONG
这里是海滨。南边是茫茫的大海。现在的风很大，海浪不时翻滚着
扑到岸边，远处可以看到几艘鱼船在那里打鱼。
LONG);

  set("exits", ([ 
 "east":__DIR__"haibin6",
 "southwest":__DIR__"haibin4",
        ]));
  set("outdoors","yangzhoubei");
  
  set("valid_startroom", 1);
  setup();
 
}

