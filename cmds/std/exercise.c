#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int finish(object me, string force_skill,int i);
int halt_exercise(object me);
string swap_msg(string arg);

int main(object me, string arg)
{
	int kee_cost, busy_time;string *force,force_skill;
	int i;string sub_force;
	seteuid(getuid());
   
	if(environment(me)->query("no_exercise")||environment(me)->query("sleep_room")
			|| (environment(me)->query("no_fight")&&!environment(me)->query("can_exercise"))
     )
		return notify_fail("这里禁止打坐练功。\n");
         
	if (me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("你现在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("战斗中不能练内功，会走火入魔。\n");
   
	force=me->query("force_skill");
	if(sizeof(force)==0)
		return notify_fail("你必须先学一种内功!\n");
	if(sizeof(force)>1){
		if( !arg||sscanf(arg, "%s %d",force_skill,kee_cost)!=2 )
			return notify_fail("你有多种内功，请使用 exercise 内功名称 花内力数.如 exercise changsheng-jue 10.\n");

		if(sizeof(force-({force_skill}))==sizeof(force))
			return notify_fail("你没有学习这种内功!\n");
	}
	else{
		if(!arg||sscanf(arg,"%d",kee_cost)!=1)
			return notify_fail("请使用 exercise 数字。\n");
		force_skill=force[0];
	}

	if( kee_cost < 10 ) 
		return notify_fail("你最少要花 10 点「气」才能练功。\n");

	if( (int)me->query("kee") < kee_cost )
		return notify_fail("你现在的气太少了，无法产生内息运行全身经脉。\n");
	if(me->query("gin")*100/me->query("max_gin")<60)
		return notify_fail("你的精神状态太差了，无法打坐运气！\n");
	
	i=SKILL_D(force_skill)->query_exercise(me);
	
	if(me->query("combat_exp")>=3000000&&me->query("env/dazuo_msg")){
		sub_force = me->query("env/dazuo_msg");
		if( strlen(sub_force) > 40 )
			sub_force = "";
		else
			sub_force = swap_msg(sub_force);
	}
	else		
		sub_force=SKILL_D(force_skill)->sub_exercise(me);
	
	if(sub_force=="") 	
   		sub_force = "$N坐下来打坐运气，一股内息开始在体内流动。\n";
   	message_vision(sub_force,me);
	sub_force=replace_string(sub_force,"$N",me->name());
	sub_force=replace_string(sub_force,"\n","");
	me->set_temp("do_exercise",1);
	me->set_temp("apply/short",({sub_force}));
	me->set_temp("kee_cost",kee_cost);
	me->start_busy((:finish,me,force_skill,i:),(:halt_exercise:));
	return 1;
}

int finish(object me,string force_skill,int i)
{
	string sub_force;int force_gain;
	int kee_cost;
	kee_cost=me->query_temp("kee_cost");
	force_gain=10+((int)me->query_skill("force",1)/3+(int)me->query_skill(force_skill,1)/2)/3;
	// me add force_gain force one second
	if(force_gain>kee_cost) force_gain=kee_cost;
	if(force_gain>me->query("kee")) force_gain=me->query("kee");
	kee_cost=kee_cost-force_gain;
	me->receive_damage("kee",force_gain);
	me->add("force", force_gain+force_gain*i/100);
	if(kee_cost<=0||me->query("kee")<=0||me->is_fighting()){
		message_vision("$N打坐完毕，吸一口气，缓缓站了起来。\n",me);
		me->delete_temp("apply/short");
		me->delete_temp("kee_cost");
		me->delete_temp("do_exercise");
		if( (int)me->query("force") >=(int)me->query("max_force") * 2) {
			if( me->query("max_force") >me->query_skill("force",1)*63/4) {
				tell_object(me, "当你的内息遍布全身经脉时却没有功力提升的迹象，似乎内力修为已经遇到了瓶颈。\n");
				me->set("force", me->query("max_force")*2);
			}
			else{
				tell_object(me, "你的内力增强了！\n");
				me->add("max_force", 1);
				me->set("force", me->query("max_force"));
			}
     
		}
		me->start_busy(1);   
		return 0;
	}
	me->set_temp("kee_cost",kee_cost);
    return 1;
}

int halt_exercise(object me)
{
	message_vision("$N强行将气息压回丹田之中，缓缓站了起来。\n",me);	
    
    if( (int)me->query("force") >=(int)me->query("max_force") * 2)
		me->set("force", me->query("max_force")*2);
    
	me->delete_temp("apply/short");
	me->delete_temp("kee_cost");
	me->delete_temp("do_exercise");
   
	return 1;
}

string swap_msg(string arg)
{
	
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);
	arg += "\n"+NOR;
	return arg;
}

int help(object me)
{
        write(@HELP
指令格式 : exercise|dazuo [<耗费「气」的量，预设值 >=10]

运气练功，控制体内的气在各经脉间流动，藉以训练人体肌肉骨骼的耐
力、爆发力，并且用内力的形式将能量储备下来。

HELP
        );
        return 1;
}
