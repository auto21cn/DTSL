
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short","大路");
  set ("long", @LONG
这里是一条大路。这条大路宽敞，这里的行人比较多。不时有人谈
笑着从你的身旁走过，也有几名武林人士朝东走去，看起来似乎是投奔
洛阳王世充的。
LONG);

  set("exits", ([ 
"west":__DIR__"dalu1",
"southeast":__DIR__"shalu1",
       ]));
 set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

