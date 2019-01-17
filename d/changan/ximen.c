
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","金光门");
  set ("long", @LONG
这是长安城的西门--金光门，这里站着几个官兵，在检查着来往的
百姓。西门是往西域的必经之地，官兵们戒备森严。一条笔直的青石板
大道向东西两边延伸。西边是郊外，骑马的、坐轿的、走路的各色行人
都很匆匆。
LONG);

  set("exits", ([ 
   "north":__DIR__"xiaolu1",
   "south":__DIR__"xiaolu2",
   "east":__DIR__"gmdajie7",
   "west":__DIR__"guandao1",
         ]));
  set("objects",([
	  __DIR__"npc/bing":2,
	  __DIR__"npc/wujiang":1,
	  ]));

  set("outdoors","changan");
  set("valid_startroom", 1);
  setup();
 
}

