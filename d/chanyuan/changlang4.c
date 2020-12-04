
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","长廊");
  set ("long", @LONG
这里是净念禅院的长廊。北面是禅院的正殿大雄宝殿。墙壁上画着
很多佛像，看上去栩栩如生。一看就是出自著名的工匠之手。
LONG);

  set("exits", ([ 
	  "north":__DIR__"daxiong-baodian",
	  "south":__DIR__"changlang5",
       ]));

  
  set("valid_startroom", 1);
  setup();
 
}

