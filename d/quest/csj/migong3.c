
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short",HIB"暗室"NOR);
	set("long", @LONG
这里是一个暗室，四周黑洞洞的，看起来错综复杂，似乎很容易迷
路。
LONG);
        set("exits",([
          "east":__DIR__"migong2",
          "west":__DIR__"migong3",
          "south":__DIR__"migong1",
          "north":__DIR__"migong4",
          "up":"/d/yangzhou/feiyuan",
          ]));
	setup();      
}
