
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","石桥");
  set ("long", @LONG
这里是一个石桥。一条小溪自西北从桥下流过。溪水中有几条游鱼
游来游去。有几名独尊堡的弟子悠闲地站在桥上聊天，看着水中的游鱼
在谈笑。
LONG);

  set("exits", ([ 
  
	  "northeast":__DIR__"shilu",
	  "south":__DIR__"zhutang",
         ]));
 set("outdoors","chengdu");
  set("valid_startroom", 1);
  setup();
 
}
