
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short","官路");
  set ("long", @LONG
这里是一条官路。此处是故地渑池，昔日秦王会猎赵王于此。而今
早已不见旧景，触景生情，不禁令英雄唏嘘不已。
LONG);

  set("exits", ([ 
"northwest":__DIR__"shalu2",
"east":__DIR__"lguanlu2",
       ]));
 set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

