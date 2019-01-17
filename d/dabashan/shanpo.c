
#include <ansi.h>
inherit ROOM;

int do_pa();
void create ()
{
  set ("short","山坡");
  set ("long", @LONG
这里是一山坡，非常倾斜，一不小心，就可能滚到了下面。东边是
一条上山的路。西边有一个山脊。看来没什么路走，只有爬(pa)上去了。
LONG);

  set("exits", ([ 

   "eastup":__DIR__"shanlu4",
           ]));

set("outdoors","dabashan");
  
  set("valid_startroom", 1);
  setup();
 
}

void init()
{
  add_action("do_pa","pa");
}

int do_pa()
{
   object me;
   me=this_player();
   if(me->query("sen")<15)
   return notify_fail("你试图爬上去，可是精神疲倦，根本使不上半点力气。\n");
   me->add("sen",-15);
   me->move(__DIR__"shanji2");
   message_vision("$N看准一个地方，用双手抓住，爬了上去。\n",me);
   tell_object(__DIR__"shanji2",me->name()+"爬了上来！\n");
   return 1;
}
