
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIG"花园"NOR);
  set ("long", @LONG
这里是一个花园。花香扑鼻而来，顿时神清目爽。仔细一看，花的
种类不是很多，多是淡雅之类，但更显出这里的超凡气氛。
LONG);

  set("exits", ([ 

  "north":__DIR__"zhengdian",
  "south":__DIR__"suishilu1",
  "east":__DIR__"huiketing",
       ]));
  set("objects",([
	  "/d/job/cihangjob/qin":1,
	  ]));
set("outdoors","jingzhai");
  
  set("valid_startroom", 1);
  setup();
 
}

