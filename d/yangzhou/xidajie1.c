
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西大街");
  set ("long", @LONG
这里是扬州城的西大街。这里已经很热闹，人来人往，络绎不绝。
南边是扬州的白马寺，这里就可以听到悠扬的诵经的声音。有很多人到
那里去烧香拜佛,但由于近来战乱,所以拜佛的人也没有以前多了。
LONG);

  set("exits", ([ 
 "east":__DIR__"xidajie2",
 "south":__DIR__"baimasi",
 "west":__DIR__"ximen",
 "north":"/d/job/timejob/guandimiao",
        ]));
  set("objects",([
   __DIR__"npc/xiangke":2,
   ]));
   
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

