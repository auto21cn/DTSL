
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIW"诵经房"NOR);
  set ("long", @LONG
这里是慈航静斋的诵经房。只见这里有很多慈航静斋的弟子，双手
合十，诵念佛经。这里的气氛庄严肃穆，听着诵经的声音，你的心神清
净了许多。
LONG);

  set("exits", ([ 

  "southeast":__DIR__"zoulang1",
    ]));
  /*set("objects",([
	  __DIR__"npc/bing":2,
	  ]));*/

  
  set("valid_startroom", 1);
  setup();
 
}

