
#include <ansi.h>

inherit ROOM;


void create ()
{
  set ("short","草地");
  set ("long", @LONG
这里是片草地。这里的行人不多。再往东走，就要出安徽而到浙江
了。这里风景秀丽，山水如画，空气清新。江水的潮湿气息扑鼻而来。
LONG);

  set("exits", ([ 

  "northeast":__DIR__"shalu1",
  "west":__DIR__"caodi1",
  
         ]));

  set("valid_startroom", 1);
  set("outdoors","jiujiang");
  setup();
 
}

