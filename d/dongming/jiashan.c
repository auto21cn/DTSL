
inherit ROOM;
#include <ansi.h>
int do_enter(string arg);
void create()
{
	set("short", GRN"假山"NOR);
	set("long", @LONG
这里是假山。假山看起来层峦迭嶂，奇秀无比。你看了看，假山上
好像有一个洞。
LONG);
	set("exits", ([
		"southeast":__DIR__"zhulin",
			]));
      set("objects",([
		  __DIR__"npc/shanyudie":1,
		  ]));
       set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

void init()
{
	add_action("do_enter","zuan");
}

int do_enter(string arg)
{
  object me;
  me=this_player();
  if(!arg||(arg!="洞"&&arg!="hole"))
	  return notify_fail("你要干什么？\n");
  if(present("shan yudie",environment(me)))
	  return notify_fail("单玉蝶拦住了你，喂，做什么呢！\n");
  message_vision("$N朝假山的洞中钻了进去！\n",me);
  me->move(__DIR__"hole");
  return 1;
}

