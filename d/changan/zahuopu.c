
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","杂货铺");
  set ("long", @LONG
这里是长安的杂货铺，在这里你可以买到生活中常用的许多物品，
老板站在柜台后面，用一双小眼睛上下打量着你，通过他的目光可以看
出他擅长经商。旁边的小二热情的向你打着招呼。
LONG);

  set("exits", ([ 
 "west":__DIR__"dongshidongjie5",
       ]));
  set("objects",([
	  __DIR__"npc/xiaoer4":1,
	  ]));
  set("valid_startroom", 1);
  setup();
 
}

