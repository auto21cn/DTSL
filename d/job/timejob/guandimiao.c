
#include <ansi.h>
inherit ROOM;
int do_jiangli(string arg);

void create ()
{
  set ("short",HIR"关帝庙"NOR);
  set ("long", @LONG
这里是扬州的关帝庙。每天来这里求平安的人很多。现在又兵荒马
乱，所以人们更愿意来这里求个平安。这里立着一个关公的塑像，手中
拿着一个青龙偃月刀，威风凛凛。
LONG);

  set("exits", ([ 
 "south":"/d/yangzhou/xidajie1",
        ]));
  set("valid_startroom", 1);
  set("target",([
     "name":"",
     "level":"",
     ]));
  set("objects",([
     __DIR__"timerobot":1,
     ]));
  setup();
 
}
