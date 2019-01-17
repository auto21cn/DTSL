
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","东门");
  set ("long", @LONG
这里是扬州城的东门。这里的行人渐渐多了起来，显得热闹起来。
自古扬州多繁华，虽然是战乱，也掩盖不了扬州的热闹气氛。这里有几
个官兵,检查着来往的行人。
LONG);

  set("exits", ([ 
"west":__DIR__"dongdajie3",
"east":"/d/job/sjbjob/gangkou",
        ]));
  set("objects",([
	  __DIR__"npc/bing":2,
	  __DIR__"npc/wujiang":1,
	  ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

