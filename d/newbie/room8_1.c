
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","药师篇");
  set ("long", @LONG
到襄阳的药店，qiuzhi shangguan就可以了。 
药师分为学本草术理的药师和学毒术的药师两种，两个只能选择一个。 
xue shangguan bencao-shuli，则成为本草术理的药师，
xue shangguan poison，则成为学毒术的药师。 
两个技能只能学到 100 级，以后靠炼制药物提高。 
具体的内容请看看 help vocation吧！
LONG);

  set("exits", ([ 
 "west":__DIR__"room8",
        ]));
  
set("no_fight",1);
set("no_exert",1);
  set("valid_startroom", 1);
  setup();
 
}

