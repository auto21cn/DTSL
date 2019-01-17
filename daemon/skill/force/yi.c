//九玄大法
//弈。

#include <ansi.h>
#include <skill.h>
		
int exert(object me, object target)
{
	
	string msg;
	
	if(target!=me)
			return notify_fail("「弈」不能用来攻击别人！\n");
	if(environment(me)->query("no_fight"))
	return notify_fail("这里不能使用这么有威胁力的内功！\n");
	if(environment(me)->query("sleep_room"))
	return notify_fail("你不要吵醒别人了！\n");
		
	if(me->query("pker"))
	return notify_fail("通缉犯还是老实点吧！\n");
	if(me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if(!me->query_skill("jiuxuan-dafa",1))
		return notify_fail("不学九玄大法如何使用「弈」？\n");
	if((int)me->query_skill("jiuxuan-dafa",1)<100)
		return notify_fail("你的九玄大法修为不够！\n");
	if((int)me->query_skill("force",1)<100)
        return notify_fail("你的基本内功修为不够！\n");
        if(me->query("force")<500)
		return notify_fail("你的内力不足以使用此内功！\n");
	if(me->query_temp("exert_jiuxuandafa"))
	return notify_fail("你正在使用九玄大法。\n");
        if(time()-me->query_temp("exert_busy/jiuxuandafa")<60)
          return notify_fail("连续施展绝技需要深厚的先天真气支持，你修为不够，如何能行？\n");
		
        me->add("force",-500);
	
	msg=HIY"$N"+HIY+"深吸一口气，顿时觉得心神具净！\n"NOR;
	message_vision(msg,me);
	me->set_temp("exert_jiuxuandafa",1);
	me->set_temp("no_receive_damage_gin",1);
	call_out("exert2",me->query_skill("jiuxuan-dafa",1)/5,me);
	
	return 1;
}

int exert2(object me)
{
   if(!me)
   return 1;
   
   message_vision("\n$N收回了九玄大法。\n\n",me);
   me->delete_temp("no_receive_damage_gin");
   me->set_temp("exert_busy/jiuxuandafa",time());
   me->delete_temp("exert_jiuxuandafa");
   return 1;
}
