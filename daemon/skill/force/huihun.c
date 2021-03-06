//天魔回魂。
#include <ansi.h>
#include <skill.h>
inherit SSERVER;

int exert(object me, object target)
{
        string msg;
        int eff_kee,time;
	
	if(target!=me)
			return notify_fail("「天魔回魂」不能用来攻击别人！\n");
	if(!me->is_fighting())
	return notify_fail("「天魔回魂」只能在战斗中使用！\n");
	if(!living(target))
		return notify_fail("那不是个活物耶！\n");
	if(me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if(me->query("eff_kee")*100/me->query("max_kee")>30)
	return notify_fail("你受得伤不重，没有必要使用「天魔回魂」。\n");
	if(!me->query_skill("tianmo-dafa",1))
		return notify_fail("不学天魔大法如何使用「天魔回魂」？\n");
	if((int)me->query_skill("tianmo-dafa",1)<160)
		return notify_fail("你的天魔大法修为不够！\n");
	if((int)me->query_skill("force",1)<160)
        return notify_fail("你的基本内功修为不够！\n");
        if(me->query("force")<300)
        return notify_fail("你目前的内力无法施展「天魔回魂」！\n");
        if(me->query("apply_points")<180)
        return notify_fail("你目前的气势无法施展「天魔回魂」！\n");
        
        if(time()-me->query_temp("exert_busy/huihun")<30)
        return notify_fail("你真气不足，无法施展「天魔回魂」！\n");
        
        if(me->query_temp("exert_action/huihun"))
        return notify_fail("你正在施展「天魔回魂」！\n");
        
        if(me->query("eff_kee")*100/me->query("max_kee")>=100)
        return notify_fail("你现在没有受伤，没有必要使用「天魔回魂」。\n");
        
        eff_kee=me->query("eff_kee");
        time=me->query_skill("tianmo-dafa",1)/20;
        if(time>10)
        time=10;
        
        msg=HIR"\n$N"+HIR+"受伤不轻，敌人却象潮水般攻来。 \n"+
            "$N"+HIR+"猛一咬牙，运起霸道的「天魔回魂」，顿时杀气冲天！\n"NOR;
        message_vision(msg,me);
	
        me->set_temp("exert_action/huihun",1);
        me->set_temp("exert_busy/huihun",time());//要有间隔时间
        me->set_temp("perform_busy",time());//使用后，不能立即使用 perform
        
        me->set("eff_kee",me->query("max_kee"));
        me->set("apply_points",0);
        me->add("force",-300);
        
        call_out("do_check",1,me,eff_kee,time);
        
        return 1;
}

void do_clear(object me)
{
        me->delete_temp("exert_action/huihun");
        me->set_temp("exert_busy/huihun",time());
        me->set_temp("perform_busy",time());
}

void do_check(object me,int eff_kee,int time)
{
    string msg;
    
    if(!me)
    return;
    if(me->is_ghost()){
     do_clear(me);
     return;
    }
    time--;
    if(time<=0){
      
      msg=HIG"\n$N口中一甜，吐出一大口鲜血，看来用「天魔回魂」压制的伤势又再度复发了。\n"NOR; 

      if(me->query("eff_kee")<eff_kee){
      	message_vision(msg,me);
      	do_clear(me);
      	return;
      }
      eff_kee=eff_kee-20;
      if(eff_kee<0) eff_kee=10;
      me->set("eff_kee",eff_kee);
      message_vision(msg,me);
      do_clear(me);
      return;
   }
   me->set("eff_kee",me->query("max_kee"));
   call_out("do_check",1,me,eff_kee,time);
}
   