
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","天井");
  set ("long", @LONG
你走进一个小天井，青石板铺路，路周围种着四季花草，西南有月
亮门通向别的院落，纵是一个小小的天井，布置的也是精巧细致，别具
匠心。
LONG);

  set("exits", ([ 
 "southeast":__DIR__"houhuayuan",
 "southwest":__DIR__"zoulang",
 //"north":"/d/clone/room/cityroom/changan",
 //"east":"/d/clone/room/orgsaferoom/lifa/baihutang",
        ]));
  
set("valid_startroom", 1);
  setup();
 
}

