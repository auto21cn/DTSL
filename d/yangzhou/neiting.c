
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","内厅");
  set ("long", @LONG
这里是扬州城的总管府的内厅。平时尉迟胜在这里处理公务。现在
兵荒马乱，这里已经形同虚设。平时更是很少有人来这里。大厅的正上
方挂着一张大匾，上面写着：忠义孝廉 四个大字。
LONG);

  set("exits", ([ 
 "out":__DIR__"zongguanfu",
 "enter":"/d/clone/room/cityroom/yangzhou",
        ]));
  set("objects",([
	  __DIR__"npc/weichisheng":1,
	  ]));
  set("valid_startroom", 1);
  setup();
 
}

