
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIW"后清殿"NOR);
  set ("long", @LONG
这里是慈航静斋的后清殿。南边是慈航静斋的正殿了。心清而神清，
神清而身清，来到这里，你不觉的心神清净，似乎会忘掉所有的烦恼。
LONG);

  set("exits", ([ 

  "north":__DIR__"suishilu2",
  "south":__DIR__"zhengdian",
      ]));
  /*set("objects",([
	  __DIR__"npc/bing":2,
	  ]));*/
  
  set("valid_startroom", 1);
  setup();
 
}

