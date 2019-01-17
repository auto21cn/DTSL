
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",GRN"钟鼓楼"NOR);
  set ("long", @LONG
“钟鼓楼钟声鼓声传千里  洛河水洛阳河阳颂太平“据说这幅对联
是隋初一位隐士所做。在这座宏伟的钟鼓楼两边，这幅对联已经悬挂了
近百年，可惜时局混乱，不知道什么时候才能有真正的太平。
LONG);

  set("exits", ([ 
  
	  "east":__DIR__"baihujie2",
	  "up":__DIR__"zhulou",
         ]));
  set("objects",([
  __DIR__"npc/houxibai":1,
  ]));
  set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object ob,string dir)
{
  if(ob->query("family/family_name")!="花间派"&&
     dir=="up")
  return notify_fail("只有花间派才可以上去！\n");
  if(ob->query("pker"))
  return notify_fail("通缉犯还是不要上去了！\n");
  return ::valid_leave(ob,dir);
}

