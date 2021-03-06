
#include <ansi.h>
inherit ROOM;

int do_ci(string arg);
void create ()
{
  set ("short","竹林");
  set ("long", @LONG
这里是竹林。这里一片葱葱郁郁，竹枝节节，迎风摆荡。想到人们
长说：以意御剑，如果用剑能每次都刺到这随风摆动的竹子，那剑术的
修为也定会有一定的提高了。
LONG);
  set("exits",([
	  "northeast":__DIR__"liangting",
	  "southwest":__DIR__"houdian",
	  ]));

  set("outdoors","yinkui");

  set("valid_startroom", 1);
  setup();
 
}

void init()
{
   add_action("do_ci","ci");
}

int do_ci(string arg)
{
   object me,weapon;
   me=this_player();
   if(!arg||arg!="竹子")
   return notify_fail("你要刺什么？\n");
   if(!objectp(weapon=me->query_temp("weapon")))
   return notify_fail("没有武器，你要用剑刺吗？\n");
   if(weapon->query("skill_type")!="sword")
   return notify_fail("你挥动"+weapon->name()+"晃了几下，发现好无用处！\n");
   if(weapon->query("flag")==1)
   return notify_fail("你沮丧的发现手中的兵刃已经断掉了！\n");
   if(me->query("sen")<20)
   return notify_fail("你精神太差了！\n");
   if(me->query_skill("sword",1)>=101)
   return notify_fail("你的基本剑法很高了，这些竹子没什么用的！\n");
   if(me->is_busy())
   return notify_fail("你正忙着呢！\n");
   message_vision(YEL"$N屏气凝神，望着在风中摆动的竹子，突然一剑刺了出去！\n"NOR,me);
   me->improve_skill("sword",me->query_int()/2+20+random(5));
   me->add("sen",-20);
   if(me->query_skill("sword",1)<50)
   message_vision("$N收剑站住，身形有些不稳。\n",me);
   else if(me->query_skill("sword",1)<100)
   message_vision("$N望着风中飘动的竹叶，不禁露出了笑意。\n",me);
   else if(me->query_skill("sword",1)<150)
   message_vision("$N收剑停身，丝毫不乱，剑法以至纯熟。\n",me);
   else if(me->query_skill("sword",1)<200)
   message_vision("$N潇洒地一收剑，宛如一代剑术高手风范。\n",me);
   return 1;
}
