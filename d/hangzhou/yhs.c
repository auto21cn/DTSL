
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","玉皇山");
  set ("long", @LONG
玉皇山林木葱绿，翠竹挺拔，亭阁众多，云雾缭绕，可以纵览西湖
和西湖周围的全部景色。西南面就到了虎跑。
LONG);

  set("exits", ([ 
  "southwest":__DIR__"hupao",
        ]));
  set("objects",([
       __DIR__"npc/daoke":2,
       ]));
set("outdoors","hangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

