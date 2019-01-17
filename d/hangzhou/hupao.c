
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","虎跑");
  set ("long", @LONG
这里青山灵秀，溪流淙淙，林木繁茂，环境幽雅。泉自后山的石英
岩中渗出，汇于一小方池中，干洌醇厚，享有天下第三泉之称。用虎跑
泉泡龙井茶，沁人心脾，誉为西湖双绝。
LONG);

  set("exits", ([ 
  "north":__DIR__"hupan",
  "southwest":__DIR__"nanan2",
  "northeast":__DIR__"yhs",
        ]));
   set("objects",([
       __DIR__"npc/daoke":1,
       ]));
set("outdoors","hangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

