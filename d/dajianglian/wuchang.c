
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short","武场");
  set ("long", @LONG
这里是大江联分舵的练武场，有几个弟子在这里练习武艺。旁边有
几名师傅在那里指点他们。
LONG);

  set("exits", ([ 
	  "east":__DIR__"caodi",
	     ]));
set("outdoors","dajiang");
  /*set("objects",([
	  __DIR__"npc/dizi":2,
	  ]));*/
  set("valid_startroom", 1);
  setup();
 
}

