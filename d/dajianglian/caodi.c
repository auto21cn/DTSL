
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short","草地");
  set ("long", @LONG
这里是一片草地。西边隐隐约约传来了吆喝的声音，好象是练习武
艺的声音。这里不时有人出入。
LONG);

  set("exits", ([ 
	  "north":__DIR__"shilu",
	  "south":__DIR__"mumen",
	  "west":__DIR__"wuchang",
	  "east":__DIR__"zhifatang",
    ]));
set("outdoors","dajiang");
  /*set("objects",([
	  __DIR__"npc/dizi":2,
	  ]));*/
  set("valid_startroom", 1);
  setup();
 
}

