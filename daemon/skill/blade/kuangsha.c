//狂沙。
#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -100

int perform(object me,object target)
{ 
   object weapon;
   int damage,flag;
   string msg;
   
   if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
   if(!me->is_fighting())
	   return notify_fail("「狂沙」只能在战斗中使用！\n");
    weapon=me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="blade")
    return notify_fail("手中无刀，如何使用「狂沙」？\n");
	if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("kuangsha-daofa"))
    return notify_fail("不学狂沙刀法如何使用「狂沙」？\n");
    if((int)me->query("max_force",1)<1000)
    return notify_fail("你的内力太低了!\n");
    if((int)me->query_skill("blade",1)<110)
    return notify_fail("你的基本刀法太差了！\n");
    if((int)me->query_skill("kuangsha-daofa",1)<110)
    return notify_fail("你的狂沙刀法还不到家！\n");
    if(me->query_skill("yanyang-dafa",1)<100)
    return notify_fail("你的炎阳大法修为太低了！\n");
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展出「狂沙」！\n");
    
    if(me->query("perform_quest/kuangsha")
      &&time()-me->query_temp("perform_busy")<10)
          return notify_fail("连续施展「狂沙绝技」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    if(!me->query("perform_quest/kuangsha")
      &&time()-me->query_temp("perform_busy")<5)
          return notify_fail("连续施展「狂沙绝技」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    if(!me->query("perform_quest/kuangsha")){
     damage=damage/2;
     flag=0;
    }else flag=1;
    
   
    msg=HIY"一声长啸，$N"+HIY+"左鞘右刀，龙卷风般往$n"+HIY+"旋转过去。交又织出锋芒雷射，攻守兼备的罩网。\n"+
        "奇异的劲气，以$N"+HIY+"为中心像沙漠刮起的狂暴风沙般，随着$N"+HIY+"的迫近，以雷霆万钧之势往$n"+HIY+"\n"+
        "袭去，最厉害处是$N"+HIY+"的每个旋转速度都有微妙的差异，教人难以预先掌握$N"+HIY+"攻势袭体的精\n"+
        "确时间。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「狂沙」只能在战斗中使用！\n");
    
    
    msg=HIR"周遭的空气像停止了流动，空寂得像没有半滴风的茫茫大漠，空气还灼热起来。一切似像\n"+
        "静止下来，包括不分昼夜的时光流逝，就像全无生机的乾旱沙漠。空气的灼热度却不断提\n"+
        "升。$N"+HIR+"舌绽春雷，暴喝一声，收到身后的$w"+HIR+"变魔法般出现在前方，以极玄奥奇异的手法，\n"+
        "身随刀走，往$n"+HIR+"击去。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「狂沙」只能在战斗中使用！\n");
   
    
    msg=HIG"$N"+HIG+"一声长啸，刀法一变，幻出流沙滚动般的刀浪，重重往$n"+HIG+"攻去，正是狂沙五诀中的“滚\n"+
        "沙诀”，$n"+HIG+"到此刻方真正领会到$N"+HIG+"的惊天功力，有如置身在狂涛怒飕之中，刀浪滚滚而来，\n"+
        "无有穷尽。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
       
    if(!flag){
    	me->set_temp("perform_busy",time());
    	return 1;
    }
    me->set_temp("perform_busy",time());
    call_out("perform2",2,me,target,weapon,damage);
    
    return 1;   
  
}

int perform2(object me,object target,object weapon,int damage)
{ 
        string msg;
        
        if(!me) return 1;
        if(!target||!living(target)){
         me->set_temp("perform_busy",time());
         return 1;
        }
        me->set_temp("perform_busy",time());
        if(!weapon||me->query_temp("weapon")!=weapon)
        return 1;
        if(me->is_busy())
        return 1;
  
        if(!me->is_fighting(target))
	   return 1;
	   
    msg=MAG"$w"+MAG+"在虚空画出一道充满旋卷味道、波浪般起伏的轨迹，变化无穷的朝$n"+MAG+"“卷”过来。虽是\n"+
        "一刀，却由十多重连绵的波卷组成，每个波卷、时间和攻击的角度都有精微的转变，送出\n"+
        "卷卷刀劲，汇为成能被墙裂壁的凌厉刀气，威力无涛。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「狂沙」只能在战斗中使用！\n");
      
    msg=WHT"$N"+WHT+"双目奇光大盛，刀收往后，全身衣袂拂扬，同时催发狂沙劲，$w"+WHT+"带起的凌厉刀气，有若\n"+
        "狂沙拂过炎旱的大漠。空中充满细砂的旋劲，像风沙般向$n"+WHT+"狂吹猛打。配合$N"+WHT+"挺拔如松柏\n"+
        "的雄伟身形，确有不动如山，渊亭岳峙的气势，更添其威风。$n"+WHT+"立时生出乾旱渴热的骇人\n"+
        "感觉。不由生出望风沙而溃败的气馁失落感。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
        
    me->set_temp("perform_busy",time());
    return 1;   
  
}
