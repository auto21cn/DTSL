
#include <ansi.h>
inherit ROOM;

int do_cai(string arg);
void create ()
{
  set ("short","深山老林");
  set ("long", @LONG
这里树木茂盛，遮住了天上的阳光。远处能听到几声鸟鸣叫的声音，
不时有野兔从你的脚旁跑过。据说这里可以挖到许多药材，所以有很多
采药人来这里采药。
LONG);

  set("exits", ([ 
  "southwest":"/d/dabashan/shanlu1",
  "northeast":"/d/dabashan/shenshan",
       ]));
set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
 
}

void init()
{
	add_action("do_cai","cai");
}

int do_cai(string arg)
{
	object me,ob,tool;
	me=this_player();
	if(!arg||arg!="药")
		return notify_fail("你想开采什么？\n");
	if(me->is_busy())
		return notify_fail("你现在很忙，歇歇吧!\n");
	if(me->is_fighting())
		return notify_fail("你还是先打完仗再说吧！\n");
	if((int)me->query_encumbrance() + 50000 > (int)me->query_max_encumbrance() ) 
         return notify_fail( "你身上的东西太多了，根本拿不动药材，还采什么啊。\n");
      message_vision("$N开采起药材来。\n",me);
    me->start_busy(1);
	me->receive_damage("sen",50+random(5));
   if(random(10)>4)
	{ob=new("/d/job/yishengjob/yao");
	ob->move((me));
	message_vision("$N开采出一颗"+ob->name()+"来！\n",me);
	}
	else
	{
		message_vision("突然一块大石从山上滚了下来！\n直接砸向$N!\n",me);
		if((int)me->query_skill("dodge",1)>=100)
		{
			message_vision("$N见势不好，连忙闪了开来！\n",me);
            ob=new("/d/job/yishengjob/yao");
	        ob->move((me));
            message_vision("$N开采出一颗"+ob->name()+"来！\n",me);
			return 1;
		}
		else
		{
		message_vision("$N被大石砸了正中！\n",me);
                ob=new("/d/job/yishengjob/yao");
	        ob->move((me));
			me->unconcious();
			return 1;
		}
	}
	return 1;
}
