
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","青石路");
  set ("long", @LONG
这里是条青石路，地上铺着整齐的青砖。这里冷冷清清的。几乎没
有什么人。南边是阴癸派的议事广场。北边就是阴癸派的正殿，那里是
阴癸派掌门宣布重大事物的地方。东边是一条弯曲的小路。
LONG);
  set("exits",([
	  "north":__DIR__"zhengdian",
	  "south":__DIR__"qingshilu1",
	  "east":__DIR__"xiaolu",
	  "westdown":__DIR__"shiwu",
	  ]));
	  
  set("objects",([
    __DIR__"npc/xiazhanglao":1,
    ]));
    
set("outdoors","yinkui");

  
  set("valid_startroom", 1);
  setup();
 
}

