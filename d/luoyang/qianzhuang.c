
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","孙记钱庄");
  set ("long", @LONG
这里是洛阳有名的钱庄。由于洛阳还很太平，所以这个钱庄的生意
一向很好。钱庄老板在那里打着算盘，不时用冷眼打量着进出的客人。
柜台的旁边放着一个大牌子，上面写着：孙记银票，全国通用。
LONG);

  set("exits", ([ 
 
  "west":__DIR__"yongdongjie2",
         ]));
  set("objects",([
	  __DIR__"npc/sun":1,
	  ]));

  
  set("valid_startroom", 1);
  setup();
 
}

