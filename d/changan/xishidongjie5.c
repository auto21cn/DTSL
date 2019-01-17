
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西市东街");
  set ("long", @LONG
你来到了闻名长安的西市－利人市，这里是利人市的东街，到处都
是前来逛集市的人。吆喝声，叫卖声不绝于耳，东面有一家水果店，西
面是一家商行。
LONG);

  set("exits", ([ 
  "north":__DIR__"xishidongjie4",
  "south":__DIR__"xishinankou2",
  "west":__DIR__"guangshenghang",
  "east":__DIR__"shuiguodian",
        ]));
  set("objects",([
         __DIR__"npc/xiaojie":1,
         
         ]));
  set("outdoors","changan");
  set("valid_startroom", 1);
  setup();
 
}

