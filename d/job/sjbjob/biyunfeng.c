
inherit ROOM;
#include <job_money.h>
void create ()
{
  set ("short","碧云峰");
  set ("long", @LONG
这里河南邙山的碧云峰。远远望去，可以看到邙山的翠云峰，据说
妖道可风的庙观就建造在那里。这里空气清新，景色秀丽，是一个游山
玩水的好地方。
LONG);

  set("exits", ([ 
"southdown":"/d/mangshan/shanlu6",
      ]));
  set("valid_startroom", 1);
  set("outdoors","mangshan"); 
  setup();
 
}

