
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"财政厅"NOR);
  set ("long", @LONG
这里是财政厅。是洛阳管理国库的地方。平时只有财政官员才可以
来这里工作。这里的警戒更加森严，侍卫平时是不会让闲杂人等进来的
。
LONG);

  set("exits", ([ 

  "west":__DIR__"zoulang1",
      ]));
  set("objects",([
	  __DIR__"npc/zhao":1,
	  ]));
  

  
  set("valid_startroom", 1);
  setup();
 
}

