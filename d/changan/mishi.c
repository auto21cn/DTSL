
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short",HIR"密室"NOR);
  set ("long", @LONG
这里是地道的尽头了，你站了起来，活动了一下筋骨。密室的中央
放着一个大桌子，上面放了盏灯。旁边的墙上还挂着一把刀。不知道是
谁居住在这里。
LONG);

  set("exits", ([ 
 "out":__DIR__"didao3",
      ]));
      set("objects",([
      __DIR__"npc/shizhixuan":1,
      ]));
  set("no_select",1);
  set("valid_startroom", 1);
  setup();
 
}
