//伏鹰枪法
//漫天风沙

#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -50


int perform(object me,object target)
{ 
    object weapon;
    int damage,flag=0;
    string msg;
    
    weapon=me->query_temp("weapon");
   
   if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
    
   if(!me->is_fighting())
   return notify_fail("「漫天风沙」只能在战斗中使用！\n");
   if(!weapon)
    return notify_fail("不拿武器，如何使用「漫天风沙」？\n");
   if(weapon->query("skill_type")!="spear")
    return notify_fail("手中无枪，如何使用「漫天风沙」？\n");
   if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("fuying-spear",1))
    return notify_fail("不学伏鹰枪法如何使用「漫天风沙」？\n");
    if(me->query("apply_points")<=0)
    return notify_fail("你的气势不足，无法使用「漫天风沙」！\n");
    
    if((int)me->query("max_force")<1000)
    return notify_fail("你的内力太低了!\n");
    if((int)me->query_skill("spear",1)<110)
    return notify_fail("你的基本枪法太差了！\n");
    if((int)me->query_skill("fuying-spear",1)<110)
    return notify_fail("你的「伏鹰枪法」还不到家！\n");
    if((int)me->query_skill("yanyang-dafa",1)<100)
    return notify_fail("你的「炎阳大法」还不到家！\n");
    
    if(me->query("perform_quest/fengsha")
    &&time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「漫天风沙」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    if(!me->query("perform_quest/fengsha")
    &&time()-me->query_temp("perform_busy")<5)
       return notify_fail("连续施展「漫天风沙」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    if(!me->query("perform_quest/fengsha"))
    damage=damage/2;//如果没解迷题。
    
    msg=HIY"一切只能以一个快字去形容，发生在肉眼难看清楚的高速下，$n"+HIY+"感到$N"+HIY+"出招时，$w"+HIY+"早已\n"+
        "刺出，化作闪电般的长虹，划过两丈的虚空，刺向$n"+HIY+"。$n"+HIY+"感到周遭所有的气流和生气都似\n"+
        "被这惊天动地的一招吸个一丝不剩，一派生机尽绝，死亡和肃杀的骇人味儿。\n"NOR;   
    
    flag=COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    
    if(!me->is_fighting())
    return notify_fail("「漫天风沙」只能在战斗中使用！\n");

    msg=HIR"$N"+HIR+"蓦地挺直身骨，全身袍袖无风自动，形态变得威猛无涛，与$n"+HIR+"相比毫不逊色，一招\n"+
        "击出，连续作出玄奥精奇至超乎任何形容的玄妙变化，却又是毫无伪假的一枪朝$n"+HIR+"的\n"+
        "$l处刺去！\n"NOR;    
     
    flag+=COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「漫天风沙」只能在战斗中使用！\n");
    
    if(!me->query("perform_quest/fengsha")){
      if(flag){
      	msg="\n$n被$N击中，浑身一震，行动顿时迟缓了！！\n";
      	message_vision(msg,me,target);
      	target->start_busy(3);      	
      }
      me->set_temp("perform_busy",time());
      return 1;
    }
    
    msg=HIG"$N"+HIG+"使的实出隔空遥制的神奇招数，仿似对$n"+HIG+"不能做成任何威胁，但是每一个手法，均以炉\n"+
        "火纯青、出神人化的伏鹰枪法，先一步隔远击中敌人，织出无形而有实的气网，如蚕吐丝，\n"+
        "而每一招在与$n"+HIG+"正面交锋的一刻积聚至爆发的巅峰，给予$n"+HIG+"致命一击。\n"NOR;
    
    flag+=COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「漫天风沙」只能在战斗中使用！\n");
    
    if(flag){
      	msg="\n$n被$N击中，浑身一震，行动顿时迟缓了！！\n";
      	message_vision(msg,me,target);
      	target->start_busy(5);      	
    }
    me->set_temp("perform_busy",time());
    return 1;   
  
}  
 
