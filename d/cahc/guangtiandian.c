
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","光天殿");
  set ("long", @LONG
这里就是李建成与其亲信议事的大殿，殿内陈设华丽，镌镂龙凤飞
镶之状，雄伟壮丽，金壁生辉。 
LONG);

  set("exits", ([ 
 "north":__DIR__"chengendian",
 "south":__DIR__"chongjiaodian",
        ]));
  
  set("valid_startroom", 1);
  setup();
 
}

