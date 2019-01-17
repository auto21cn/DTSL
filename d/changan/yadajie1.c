
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","永安大街");
  set ("long", @LONG
这是永安大街，北面连接长安城的景耀门，西面和永安大渠平行纵贯
长安。这里属于长安南里，西面过了渠就是闻名的西市，这里有人大做买
卖，有摆小摊卖烧饼与脆麻花的，有炸油糕、卖鸡蛋的，热闹非常。
LONG);

  set("exits", ([ 
 "north":__DIR__"xishidongkou2",
 "south":__DIR__"xpdajie2",
         ]));
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

