//五霸刀法
//绝魂斩
//by rzy 02.09.24

#include <ansi.h>
inherit SSERVER;

#define REDUCE_DEX -100

int perform(object me,object target) {
	object weapon;
	int damage=50+me->query("apply_points")*3/2;
	string msg;

	weapon=me->query_temp("weapon");

	if(!target)
          if(!objectp(target=offensive_target(me)))
		return notify_fail("目前你没有攻击的目标！\n");
	if(!me->is_fighting())
		return notify_fail("「绝魂斩」要在战斗中使用！\n");
	if(!weapon)
		return notify_fail("空手无法使用「绝魂斩」！\n");
	if(weapon->query("skill_type")!="blade")
		return notify_fail("你使用的武器不对！\n");
	if(weapon->query("flag")==1)
		return notify_fail("断掉的兵器不能再使用了！\n");
	if(!me->query_skill("wuba-daofa",1))
		return notify_fail("你不会「五霸刀法」！\n");
	if(me->query("apply_points")<=0)
		return notify_fail("你的气势不足，无法使用「绝魂斩」！\n");
	if((int)me->query("max_force")<1500)
		return notify_fail("以你的内力修为，使不出「绝魂斩」这种绝技！\n");
	if((int)me->query("force")<500)
		return notify_fail("你的内力不够！\n");
	if((int)me->query_skill("blade",1)<110)
		return notify_fail("你的基本刀法太差了！\n");
	if((int)me->query_skill("wuba-daofa",1)<110)
		return notify_fail("你的「五霸刀法」还不到家！\n");
	if((int)me->query_skill("jiuxuan-dafa",1)<110)
		return notify_fail("你的「九玄大法」还不到家！\n");
	if(time()-me->query_temp("perform_busy")<10)
		return notify_fail("连续施展「绝魂斩」需要深厚的先天真气支持，你修为不够，如何能行？\n");
	if(me->query_skill("yijian-shu",1)<100)
		return notify_fail("你的弈剑术修为太低了！\n");

	msg=HIR"$N"+HIR+"凝神闭目，$w"+HIR+"自背至头顶划出一条优美的曲线，$w"+HIR+"行至头顶忽然一顿，瞬间气势达到顶峰，\n"
		"双目精光绽放，天马行空的一刀急劈而下！ \n"NOR;   
	
	COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
	
	me->set("apply_points",0);
		
	me->set_temp("perform_busy",time());
	return 1;

}