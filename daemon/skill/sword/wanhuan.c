//千变万幻。
#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -100

void show_msg(object me,object victim)
{
    string str;
    
     if (userp(victim)&&
          (victim->query("eff_kee")<0 || 
          !living(victim) 
          )
        )   {
          str="听说"+victim->name()+""HIM"死在"+me->name()+""HIM"的"HIY"千变铜萧"HIM"之下，面带诡异的笑容，恐怖异常！"NOR;
                        message("channel:rumor",HIM"【谣言】某人："+str+"\n"NOR,users());
     }
     return;
}

int perform(object me,object target)
{ 
    object weapon;
    string msg;
    int damage,flag;
    
    flag=0;
   if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
   if(!me->is_fighting())
	   return notify_fail("「千变万幻」只能在战斗中使用!\n");
    weapon=me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="sword")
    return notify_fail("手中无剑，如何使用「千变万幻」？\n");
    if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("qianbian-tongxiao"))
    return notify_fail("不学「千变铜萧」如何使用「千变万幻」？\n");
    if((int)me->query("max_force",1)<1500)
    return notify_fail("你的内力太低了!\n");
    if((int)me->query_skill("sword",1)<160)
    return notify_fail("你的基本剑法太差了！\n");
    if((int)me->query_skill("qianbian-tongxiao",1)<160)
    return notify_fail("你的「千变铜萧」还不到家！\n");
    if((int)me->query_skill("tianmo-dafa",1)<150)
    return notify_fail("你的「天魔大法」还不到家！\n");
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展「千变万幻」！\n");
    if(time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「千变万幻」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    
    if(!me->query("perform_quest/wanhuan"))
    damage=damage/2;
    
    msg=HIC"$N"+HIC+"的$w"+HIC+"发出尖锐的破空啸声，在头上画出一个又一个的圈子，\n"+
    "每个旋圈，$w"+HIC+"的真气均会随之增聚。两眼则一瞬不瞬的瞧看$n"+HIC+"，神情傲视天下。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「千变万幻」只能在战斗中使用!\n");
    
    msg=YEL"$N"+YEL+"的真气诡异的通过$w"+YEL+"，顿时发出“嗡”的一声，$n"+YEL+"不由全身一震，\n"+
    "以声制敌，确实神乎奇极，却又诡异非常！\n"NOR;
    
    flag = COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「千变万幻」只能在战斗中使用!\n");
    
    if(flag){
       msg=HIR"\n$N"+HIR+"脚踏奇步，身形不断变化，倏地$w"+HIR+"点出，只指$n"+HIR+"眉心，招数简单，\n"+
       "$w"+HIR+"却发出如同处子呻吟的古怪声音，$n"+HIR+"顿时气势全消。\n\n"NOR;
       msg=replace_string(msg,"$w",weapon->name());
       message_vision(msg,me,target);
       target->set("apply_points",target->query("apply_points")/5);
    }
    
    msg=HIR"$N"+HIR+"随手掷出$w"+HIR+"，只见$w"+HIR+"象遥控在$N"+HIR+"手中似的，遥遥的击向$n"+HIR+"，$N"+HIR+"真气一发即收，\n"+
        "在$n"+HIR+"周围画着轨迹怪异圈子的$w"+HIR+"，忽的重新回到$N"+HIR+"的手中，让人嘡目结舌。 \n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
   me->set_temp("perform_busy",time());
   show_msg(me,target);
    return 1;   
  
 }  

