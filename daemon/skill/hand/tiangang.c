//天罡拳
//天罡降兵。

#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -50

int perform(object me,object target)
{ 
   object weapon;
   string msg;
   int damage,flag=0;
   
    weapon=me->query_temp("weapon");
    if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
    if(!me->is_fighting())
    return notify_fail("「天罡降兵」只能在战斗中使用!\n");
    if(weapon)
    return notify_fail("拿着武器，如何使用「天罡降兵」？\n");
    if(me->query("PKS")>=5)
        return notify_fail("你罪孽深重，无法使用此绝技了！");
    if(!me->query_skill("tiangang-quan",1))
    return notify_fail("不学「天罡拳」如何使用「天罡降兵」？\n");
    if((int)me->query("max_force")<1000)
    return notify_fail("你的内力修为太低了!\n");
    if((int)me->query_skill("cuff",1)<110)
    return notify_fail("你的基本拳法太差了！\n");
    if((int)me->query_skill("tiangang-quan",1)<110)
    return notify_fail("你的「天罡拳」还不到家！\n");
    if((int)me->query_skill("wuxiang-shengong",1)<100)
    return notify_fail("你的「无相神功」还不到家！\n");
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展「天罡降兵」！\n");
    if(me->query("perform_quest/tiangang")
      &&time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「天罡降兵」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    if(!me->query("perform_quest/tiangang")
      &&time()-me->query_temp("perform_busy")<5)
       return notify_fail("连续施展「天罡降兵」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    if(!me->query("perform_quest/tiangang"))
    damage=damage/2;
    
    msg=MAG"$N"+MAG+"低垂的眼帘往上扬起，露出一对深邃难测，充满哲人圣者智慧的神光，接著灰色的僧\n"+
        "袍往下凹陷，紧贴全身，一拳击出。动作行云流水，又若羚羊挂角，玄机暗含。\n"NOR;
    
    flag=COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,0,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「天罡降兵」只能在战斗中使用!\n");
    
    msg=MAG"$N"+MAG+"双拳汇集了全身的内力，顿时全身衣衫鼓胀，双目放出惊人的光芒，在$n"+MAG+"吃惊之际，\n"+
        "$N"+MAG+"的双拳已如流星闪电般挥出，只见一股强大的气流朝$n"+MAG+"击去！"NOR;
    
    flag +=COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,0,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「天罡降兵」只能在战斗中使用！\n");
    
    if(!me->query("perform_quest/tiangang")){
    	me->set_temp("perform_busy",time());
    	return 1;
    }
    if(flag>0){
      msg="\n\n$N和$n的内力撞击在一起，只听“砰”的一声，将两人震退数步，\n"+
          "两人均是面色苍白，身形摇晃！\n\n";
      message_vision(msg,me,target);
      me->set("force",0);
      target->set("force",0);
    }    
    me->set_temp("perform_busy",time());
    return 1;   
  
}  
 
