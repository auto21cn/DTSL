
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","五云峰");
  set ("long", @LONG
五云峰，位于积金峰东南，山峰险峻。据传说，三茅君曾各乘五色
彩云在峰顶上空观看容山八景，后峰巅常有五色云彩出现，故名五云峰。
经五云峰南望东峰峭壁，可见黄、白色相间的花岗岩石，形如巨掌，称
“华岳仙掌”，为关中著名八景之一，
LONG);

  set("exits", ([ 
 "northdown":__DIR__"canglongling",
 "southup":__DIR__"jinsuoguan",
       ]));
  /*set("objects",([
	  __DIR__"npc/yao":1,
	  ]));*/
   set("valid_startroom", 1);
   set("outdoors","huashan");
  setup();
 
}
