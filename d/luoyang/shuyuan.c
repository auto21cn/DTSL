
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","白鹿书院");
  set ("long", @LONG
这里是洛阳著名的白鹿书院，专门负责为朝廷培养人才，可惜现在
战乱频繁，崇武之风大盛，已经决少有人来这里求教治国之道了。
LONG);

  set("exits", ([ 
 "west":__DIR__"nanjie1",
       ]));
  set("valid_startroom", 1);
  setup();
 
}

