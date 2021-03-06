//行云九步。
//逆天遁术。


#include <ansi.h>
#include <skill.h>
inherit SSERVER;

int perform(object me,object target)
{
        string msg,*doors,way;
        mapping exits;
        object room;
        int ap,vp;
  		
	if(!objectp(target=offensive_target(me)))
	 return notify_fail("你没有和别人交手，没必要使用「逆天遁术」！\n");
	 
	if(!me->is_fighting())
	return notify_fail("「逆天遁术」只能在战斗中使用！\n");
	if(me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if(!me->query_skill("xingyun-dodge",1))
		return notify_fail("不学行云九步如何使用「逆天遁术」？\n");
	if((int)me->query_skill("xingyun-dodge",1)<100)
		return notify_fail("你的行云九步修为不够！\n");
	if((int)me->query_skill("dodge",1)<100)
		return notify_fail("你的基本轻功修为不够！\n");
	if(me->query("apply_points")<=0)
	return notify_fail("你的气势不足以使用「逆天遁术」！\n");
	
	if(time()-me->query_temp("perform_busy")<3)
      return notify_fail("连续施展「逆天遁术」需要深厚的先天真气支持，你修为不够，如何能行？\n");

        exits=environment(me)->query("exits");
        if(sizeof(exits)<=0)
        return notify_fail("这里没有出口，你无法使用「逆天遁术」！\n");
        if(!me->query("startroom"))
        return notify_fail("你没有逃命的地方，无法施展「逆天遁术」！\n");
        room=load_object(me->query("startroom"));
        if(!room)
        return notify_fail("你没有逃命的地方，无法施展「逆天遁术」！\n");
        
        msg=HIG"\n$N"+HIG+"身形如烟般飘动，正是弈剑派的秘招「逆天遁术」！\n"NOR;
        message_vision(msg,me);
        
        ap=target->query_dex();
        vp=me->query_dex()+me->query_skill("xingyun-dodge",1)/5;
        
        if(random(ap+vp)>vp){
         msg=YEL"\n$n"+YEL+"反应奇快，身形一闪，拦住了$N"+YEL+"的去路！\n"NOR;
         message_vision(msg,me,target);
        }
        else{
         msg=HIY"\n$N"+HIY+"身形散去，$N"+HIY+"已经无影无踪，只剩下懊恼的$n"+HIY+"。\n"NOR;
         message_vision(msg,me,target);
         me->move(room);
         me->set("force",0);
         me->set("apply_points",0);
        }
         
        
        me->set_temp("perform_busy",time());
        return 1;
}

