
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","神女堤");
  set ("long", @long
神女堤与洛水堤旁的景色又是不同，各种假山奇石星罗其间，让人
感觉如入仙境，更让人感叹杨广的奢侈残暴。
long);

  set("exits", ([ 
  
  "north":__DIR__"matou2",
  "west":__DIR__"tianjie3",
  "east":__DIR__"shennvdi2",
         ]));

  set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

