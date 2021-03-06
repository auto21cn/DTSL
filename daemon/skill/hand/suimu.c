//木人的 perform

#include <ansi.h>

inherit SSERVER;

int perform(object me,object target)
{ 
   object weapon;
   string msg;
   int damage;
   
    weapon=me->query_temp("weapon");
    
    if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
    if(!me->is_fighting())
    return notify_fail("「碎木」只能在战斗中使用!\n");
   
    if(time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「碎木」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=target->query("max_pot")-60;
    
    if(target->query("combat_exp")<150000)
    damage=damage/2;
    
    msg="$N体内机关突然发动，立刻攻势如潮水涌来，其中招式不差于武林各派的绝学！\n"NOR;
    me->add_temp("apply/damage",damage);
    me->set_temp("action_msg",msg);
    COMBAT_D->do_attack(me,target,0,0,2);
    if(!me) return 1;
    me->add_temp("apply/damage",-damage);
    me->delete_temp("action_msg");
    
    if(!me->is_fighting())
    return notify_fail("「碎木」只能在战斗中使用!\n");
    
    msg="$N突然上身弹起，只见腹部又出现三个木拳头，冷不防朝$n打去！\n"NOR;
    me->add_temp("apply/damage",damage);
    me->set_temp("action_msg",msg);
    COMBAT_D->do_attack(me,target,0,0,2);
    if(!me) return 1;
    me->add_temp("apply/damage",-damage);
    me->delete_temp("action_msg");
    
    if(!me->is_fighting())
    return notify_fail("「碎木」只能在战斗中使用!\n");
    
    msg="$N突然手脚缩到了身体里，宛如一个圆桶，朝$n的$l处撞去！\n"NOR;
    me->add_temp("apply/damage",damage);
    me->set_temp("action_msg",msg);
    COMBAT_D->do_attack(me,target,0,0,2);
    if(!me) return 1;
    me->add_temp("apply/damage",-damage);
    me->delete_temp("action_msg");
    
        me->set_temp("perform_busy",time());
    return 1;   
  
}  
 
