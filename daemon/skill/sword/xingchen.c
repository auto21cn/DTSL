//九转剑诀
//九转星辰
#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX 100

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
	   return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    weapon=me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="sword")
    return notify_fail("手中无剑，如何使用「九转星辰 」？\n");
    if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("jiuzhuan-jianjue",1))
    return notify_fail("不学「九转剑诀」如何使用「九转星辰 」？\n");
    if((int)me->query("max_force",1)<1500)
    return notify_fail("你的内力太低了!\n");
    if((int)me->query_skill("sword",1)<160)
    return notify_fail("你的基本剑法太差了！\n");
    if((int)me->query_skill("jiuzhuan-jianjue",1)<160)
    return notify_fail("你的「九转剑诀」还不到家！\n");
    if((int)me->query_skill("jiuxuan-dafa",1)<150)
    return notify_fail("你的「九玄大法」还不到家！\n");
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展「九转星辰 」！\n");
    if(me->query("perform_quest/xingchen")
      &&time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「九转星辰」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    if(!me->query("perform_quest/xingchen")
      &&time()-me->query_temp("perform_busy")<5)
       return notify_fail("连续施展「九转星辰」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    
    if(!me->query("perform_quest/xingchen"))
    damage=damage/3;
    else damage=damage/2;
    
    msg=HIG"$N"+HIG+"的$w"+HIG+"生出包括全无欣赏心情的$n"+HIG+"大为惊叹的变化，以毫厘之差避过$n"+HIG+"的攻击，接\n"+
        "着身躯像陀螺般立定转动，$w"+HIG+"迥绕，疾刺$n"+HIG+"的$l，狠辣至极点。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    msg=HIY"$N"+HIY+"剑尖遥指$n"+HIY+"，不住颤震，似是怕得发抖，只有首当其冲的$n"+HIY+"感到那是一种玄奥的剑法，\n"+
        "能把全身功力积聚创锋，且取向变化无定，教其难以揣测。此剑若攻来，将是洞穿山河\n"+
        "之势！\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
        
    msg=MAG"$N"+MAG+"手中$w"+MAG+"泛起青湛湛的异芒，画出超乎人间美态，具乎天地至理的动人线条，四周\n"+
        "的真气像铁遇磁石般被吸引，改成水流般窜往$w"+MAG+"的锋尖，刹那间累凝而成一球烟雾，剑\n"+
        "锋化为一点青光，似若云霞缭绕里的不灭星光，流星般往$n"+MAG+"双目间的位置奔来。此点星\n"+
        "光有如勾魂摄魄的魔力，美至极点，可怕至极点。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    if(!me->query("perform_quest/xingchen")){    
      me->set_temp("perform_busy",time());
      return 1;
    }
    me->set_temp("perform_busy",time());
    call_out("perform2",3,me,target,weapon,damage);
    
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
       
    msg=HIG"$N"+HIG+"唇角逸出一丝笑意，$w"+HIG+"发出的剑气，把$n"+HIG+"紧紧锁紧，似攻似守，逢隙必入的攻来，\n"+
        "倏地$n"+HIG+"身前现出漫空星点，每一点都似乎在向$n"+HIG+"攻来，又每一点都像、水恒不动，有如\n"+
        "天上的星空，在变化周移中自具恒常不变的味道。动作行云流水，生出连绵不断的持续感觉。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    msg=HIY"$N"+HIY+"唇角逸出另一丝笑意，手中$w"+HIY+"点中$n"+HIY+"却没有发出应有的劲响，凭借绝世功力，以隔\n"+
        "山打牛的方法，化去$n"+HIY+"的劲力，$w"+HIY+"破掉$n"+HIY+"的招数后，昼出一道美丽的弧线，先往$n"+HIY+"左侧\n"+
        "弯出，再弯回来。生出强大的吸摄力，$n"+HIY+"如铁遇磁地被$w"+HIY+"牵引得往左扯去！\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    msg=HIG"$N"+HIG+"露出赞赏神色，$w"+HIG+"像在空中狂草疾书级画出无数深具某种难言美态的线条，瞧得\n"+
        "$n"+HIG+"眼花缭乱，无从入手，不知该攻向何处，倏忽间$N"+HIG+"又把制动权操诸手上。以人奕剑，\n"+
        "以剑奕敌，$N"+HIG+"仍是着着领先，牵善$n"+HIG+"的鼻子走。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    me->set_temp("perform_busy",time());
    call_out("perform3",3,me,target,weapon,damage);
    
    me->add("apply_points",50);
    me->set_temp("perform_busy",time());
    return 1;
}

int perform3(object me,object target,object weapon,int damage)
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
       
    msg=HIG"$N"+HIG+"一阵长笑，$w"+HIG+"画出一个无形却有实的剑圈，剑圈难以觉察的逐渐扩大，剑气微妙\n"+
        "地一圈一圈增加。其中心恰是$n"+HIG+"攻击之处，$n"+HIG+"的真气如水遇干棉地被吸啜得一滴不剩，\n"+
        "不能形成任何威胁，这一招更使不下去。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    msg=HIY"$N"+HIY+"倏地剑光大盛，$N"+HIY+"在气机牵引下，手上青芒暴涨，$w"+HIY+"将一个一个由小至大的气环串\n"+
        "套剑身，随着剑前推，如龙吐珠的把从小至大的气环往$n"+HIY+"送来，在击中$n"+HIY+"一刻，气环由\n"+
        "大化小，采积至巅掌的剑气将以电光石火的高速聚拢。充斥非人力可以抗拒的惊人剑气。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「九转星辰 」只能在战斗中使用!\n");
    
    msg=HIC"$N"+HIC+"身躯轻颤，$w"+HIC+"爆起的千万光点消去，$w"+HIC+"似若无中生有的现于眼前，依循着尽得大地\n"+
        "至理的完美路线，从右侧弯击而来，剑气把$n"+HIC+"完全笼罩。此招根本是挡无可挡，此剑若\n"+
        "攻来，将是洞穿山河之势。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
   
    me->set("apply_points",0);
    me->set_temp("perform_busy",time());
    return 1;
}
