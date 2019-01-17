
#include <room.h>

inherit ROOM;

int do_action(string arg);

void create()
{
	set("short", "练武场");
	set("long", @LONG
这里是石龙武馆的练武场，是石龙武馆初级弟子学习武功的地方。
你可以在这里走梅花桩来提高自己的武功。只见这里尘土飞扬，数名弟
子正在那里练得热闹。
LONG
);


	set("exits", ([
		"west" :__DIR__"beilang1",
		"east":__DIR__"wuchang3",
		"south":__DIR__"wuchang4",
		"north":__DIR__"wuchang5",
               
	]));
	/*set("objects",([
	     __DIR__"npc/dizi":1,
	    ]));*/
       set("no_fight",1);
       set("lianwu","梅花桩");
       set("over_work","你的梅花桩已经练习得可以了，可以去找教头了[task ok]。\n");
       set("work_msg",({
       "你站在梅花桩上不停地走动，觉得武学的修为有了进一步的提高！\n",
       "你在梅花桩上飞速走动，觉得自己的技能有了些提高。\n",
       "你在梅花桩上闪转腾挪，身法越来越轻盈了。\n",
       }));
       set("outdoors", "slwg");
	setup();
}

void init()
{
  add_action("do_action","lianwu");
}

#include "work_skill.c"