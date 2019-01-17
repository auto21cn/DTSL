
#include <ansi.h>
inherit ROOM;


void create ()
{
 set ("short","甘露殿");
  set ("long", @LONG
甘露殿平面呈正方形，面阔、进深各为三间，四面出廊，金砖铺地，
屋顶为单檐四角攒尖，屋面覆黄色琉璃瓦，中为铜胎鎏金宝顶。殿四面
开门，正面三交六椀槅扇门十二扇，东、北、西三面槅扇门各四扇，门
前石阶东西各一出，南北各三出，中间为浮雕云龙纹御路，踏跺、垂带
浅刻卷草纹。殿内设地屏宝座。
LONG);

  set("exits", ([ 
 "north":__DIR__"yanjiadian",
 "south":__DIR__"liangyidian",
 "eastdown":__DIR__"dongyuchi",
 "westdown":__DIR__"xiyuchi",
        ]));
set("objects",([
	  "/d/changan/npc/wangtong":1,
	  ]));
 
  set("valid_startroom", 1);
  setup();
 
}

