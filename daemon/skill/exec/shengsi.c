//不死印
//生死法
//by rzy 02.09.20

#include <ansi.h>
inherit SSERVER;

int execute(object me,object victim) {
	int i;
	string msg;

	if(victim!=me)
		return notify_fail("你不能对别人使用这个心法。\n");
	
	if(me->query_skill("huachan",1))
		return notify_fail("你学了画禅，无法施展不死印！\n");
	if(me->query_skill("busi-yin",1)<130)
		return notify_fail("你的不死印修为不够！\n");
	if(me->query_temp("execute_shengsi"))
		return notify_fail("你正在使用「生死法」！\n");
	if(time()-me->query_temp("execute_busiyin_busy")<10)
		return notify_fail("你刚刚施用用过「生死法」，现在内息还未平复。\n");  
	if(me->query("max_force")<2000)
		return notify_fail("你的内力修为无法使出「生死法」！\n");
	if(me->query("force")<1000)
		return notify_fail("你的内力不足！\n");


	message_vision(HIW"\n$N"+HIW+"双手蓦然急旋，化做龙卷风暴，"+HIY+"生出贯满全部空间的狂飚激啸！\n"+
			HIG+"\n一刹那间又变的细密如织，"+MAG+"阴柔内劲有如千丝万缕。\n\n"+
			HIR+"如此诡异的变化，只有融会生死两个极端的"+HIC+"不死印法"+HIR+"始能办到，真是生可变为死，死可变为生！\n"NOR,me);
		i=me->query_skill("busi-yin",1)*2/3+me->query("apply_points");
		me->add_temp("apply/damage",i);
		me->set_temp("execute_shengsi",1);
		me->add("force",-500);

		call_out("rid_damag",me->query_skill("busi-yin",1)/10,me,i);
		return 1;   
}

void rid_damag(object me,int i) {
	if(!me)
		return;
	message_vision(HIC"\n$N"+HIC+"的目光变得寒如冰雪，似是不含任何人类的感情，忽然又宝相乍现，$N轻叹一声，\n缓缓吐气收回了生死法。\n"NOR,me);
	me->add_temp("apply/damage",-i);
	me->delete_temp("execute_shengsi");
	me->set_temp("execute_busiyin_busy",time());
	return;
}