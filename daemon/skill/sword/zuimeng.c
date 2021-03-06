//飘梦剑法
//醉梦
//by rzy 20.09.24

#include <ansi.h>
inherit SSERVER;

int perform(object me,object target) {
        
        int damage=me->query("apply_points")*2;
        object weapon;
        int ap,vp;
        
        weapon=me->query_temp("weapon");
        
        if(!target)
          if(!objectp(target=offensive_target(me)))
        	return notify_fail("目前你没有攻击的目标！\n");
        if(!me->is_fighting())
                return notify_fail("只有在战斗时才可以使用「醉梦」！\n");
        if(!weapon)
        	return notify_fail("空手无法使用「醉梦」！\n");
        if(weapon->query("skill_type")!="sword")
                return notify_fail("你使用的武器不对！\n");
        if(weapon->query("flag")==1)
        	return notify_fail("断掉的兵器不能再使用了！\n");
        if((int)me->query_skill("bihai-force",1)<110)
        	return notify_fail("你的「碧海神功」修为太低！\n");
        if(!me->query_skill("piaomeng-jianfa",1))
                return notify_fail("你还没有学会「飘梦剑法」！\n");
        if((int)me->query("max_force")<1500)
                return notify_fail("以你的内力修为无法使出「醉梦」这样的招数！\n");
        if((int)me->query_skill("piaomeng-jianfa",1)<110)
                return notify_fail("你的「飘梦剑法」还不够娴熟！\n");
        if((int)me->query_skill("sword",1)<110)
                return notify_fail("你的基本剑法还不到家！\n");
	if(me->query("apply_points")<=0)
		return notify_fail("你的气势不足，无法使用「醉梦」！\n");
        if(time()-me->query_temp("perform_busy")<10)
                return notify_fail("连续施展「醉梦」需要深厚的先天真气支持，你修为不够，如何能行？\n");
        if(me->query_skill("dongming-xinfa",1)<100)
		return notify_fail("你的东溟心法修为太低了！\n");
        
	message_vision(HIY"\n$N"+HIY+"身形踉跄，手中"+weapon->name()+HIY+"捏拿的歪歪斜斜，却突然从意想不到的角度刺出，一瞬间发出凛冽的刺破空气之 \n"+
			"声，竟似是以内力御剑刺穴，如此招数端得不可小看！ \n"NOR,me,target);
	
	ap=me->query_dex()+me->query_int()+me->query("combat_exp")/50000;
        vp=target->query_int()+target->query_dex()+target->query("combat_exp")/50000;
   	
        if(random(ap+vp)>vp) {
        	
		if(random(ap+vp)>vp) {
			message_vision(HIR"\n"+target->name()+HIR+"没有留神这乍看下毫不起眼的招数，瘁不及防下被剑气击中，绕乱了内息，$N"+HIR+"此招隐藏的 \n"+
					"两种变化攻击已然袭体。\n"NOR,me);
                	
                	me->add_temp("apply/damage",damage);
			COMBAT_D->do_attack(me,target,weapon,0,2);
			COMBAT_D->do_attack(me,target,weapon,0,2);
			me->add_temp("apply/damage",-damage);
        	}
        	else {
        		message_vision(HIG"\n"+target->name()+HIG+"觉出此招不可小觑，沉气凝神以硬挡下了激射的剑气，却没料到$N"+HIG+"此招后段仍有诸般变化，\n"+
        				"剑气过后两道剑光迎面袭来！\n"NOR,me);
			me->add_temp("apply/damage",damage/2);
			COMBAT_D->do_attack(me,target,weapon,0,2);
			COMBAT_D->do_attack(me,target,weapon,0,2);
			me->add_temp("apply/damage",-damage/2);
		}

	}
	me->set_temp("perform_busy",time());
	return 1;
}

