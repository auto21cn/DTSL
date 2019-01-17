
#include <ansi.h>
inherit ROOM;

int do_jump(string arg);
void create ()
{
  set ("short","水潭");
  set ("long", @LONG
这里是一个水潭。潭水清澈见底，水下的东西看得清清楚楚。从这
里可以看到远方的悬崖。
LONG);

  set("exits", ([ 
 "south":__DIR__"shanlu3",
      ]));
  set("outdoors","emeishan");
 set("valid_startroom", 1);
  setup();
 
}

void init()
{
	add_action("do_jump",({"jump","tiao"}));
	add_action("do_qian","qian");
}

int do_jump(string arg)
{
	object me;
	me=this_player();
	if(!arg||(arg!="潭"&&arg!="水潭"))
		return notify_fail("你要往哪里跳？\n");
	message_vision("$N一个猛子朝潭中跳去！\n",me);
	me->move(__DIR__"tandi");
	return 1;
}
int do_qian(string arg)
{
	object me;
	me=this_player();
	
	if(!arg||(arg!="水"&&arg!="shui"))
		return notify_fail("你要做什么？\n");
	message_vision("$N一个猛子朝潭中跳去！\n",me);
	me->move("/d/clone/room/iron/room3");
	return 1;
}