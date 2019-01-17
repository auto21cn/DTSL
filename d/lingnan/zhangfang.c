
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","帐房");
  set ("long", @LONG
这里是宋家堡的帐房。处理宋家堡的一切生意事物。宋家堡在全国
均有生意，所以每天要派很多的宋家堡弟子去全国各地查账，有很多宋
家堡弟子不停地在这里进出，显得这里非常热闹。
LONG);

  set("exits", ([ 

  "east":__DIR__"qingshilu2",
      ]));
  set("objects",([
	  __DIR__"npc/zhao":1,
	  ]));
 set("no_fight",1); set("no_exert",1);

  set("valid_startroom", 1);
 
  setup();
 
}

