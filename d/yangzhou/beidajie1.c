
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","北大街");
  set ("long", @LONG
这里是扬州城的北大街。南面是扬州的瘦西湖，北面是扬州的五大
集市之一--北集市。这里讨价还价的声音，叫卖的声音不绝，热闹非凡。
东边是扬州的比武看台，不时从那里传来呼喝叫的声音。
LONG);

  set("exits", ([ 
 "north":__DIR__"beijishi",
 "west":__DIR__"dangpu",
 "southwest":__DIR__"guangchang",
//"east":"/d/clone/room/leitai/kantai1",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

