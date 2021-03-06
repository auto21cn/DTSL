//色空剑法
//空
#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -125

int perform(object me,object target)
{ 
    object weapon;
    string msg;
    int damage;
    
   if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
   if(!me->is_fighting())
	   return notify_fail("「空」只能在战斗中使用!\n");
    weapon=me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="sword")
    return notify_fail("手中无剑，如何使用「空」？\n");
    if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("sekong-jianfa",1))
    return notify_fail("不学「色空剑法」如何使用「空」？\n");
    if((int)me->query("max_force",1)<1500)
    return notify_fail("你的内力太低了!\n");
    if((int)me->query_skill("sword",1)<160)
    return notify_fail("你的基本剑法太差了！\n");
    if((int)me->query_skill("sekong-jianfa",1)<160)
    return notify_fail("你的「色空剑法」还不到家！\n");
    if((int)me->query_skill("qingxin-force",1)<150)
    return notify_fail("你的「清心普善诀」还不到家！\n");
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展「空」！\n");
    if(me->query("perform_quest/kong")
      &&time()-me->query_temp("perform_busy")<10)
       return notify_fail("连续施展「空」字决需要深厚的先天真气支持，你修为不够，如何能行？\n");
    if(!me->query("perform_quest/kong")
      &&time()-me->query_temp("perform_busy")<5)
       return notify_fail("连续施展「空」字决需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    damage=me->query("apply_points");
    
    if(!me->query("perform_quest/kong"))
    damage=damage/2;
    
    msg=HIC"电光激闪，剑气漫空。$N"+HIC+"的$w"+HIC+"化作满天光影，把$n"+HIC+"笼罩其中。$N"+HIC+"却像翩翩起舞的仙子，\n"+
        "在剑光中若隐若现，似被淡云轻盖的明月，森寒的剑气飘摇往来之势有若狂风刮起的旋雪。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「空」只能在战斗中使用!\n");
    
    msg=HIG"在神奇玄奥的招式、飘逸如仙的身法下，$N"+HIG+"每剑都能洞悉先机，彻底瓦解了$n"+HIG+"伺隙的反\n"+
        "攻。$N"+HIG+"这温柔娇婉、动人抚媚的美女那只欺霜赛雪的纤手使出这有如疾雨狂风般的可怕剑\n"+
        "法，实在令人叹为观止！\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「空」只能在战斗中使用!\n");
        
    msg=MAG"$N"+MAG+"的剑法绝无成规，但每击出一剑，都是针对$n"+MAG+"的弱点，每一剑都有千锤百练之功，\n"+
        "巧夺天地之造化。最厉害是$N"+MAG+"剑锋发出的剑气，有若泻地的水银般无隙不入，教人防不胜\n"+
        "防。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「空」只能在战斗中使用!\n");
    
    if(!me->query("perform_quest/kong")){    
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
       
    msg=HIG"蓦地眼前光华大盛，$w"+HIG+"活像天外骤来的闪电般，破开乌云密布的黑夜，当胸搠至。\n"+
        "看似简单的一剑，实包含无比玄奥的心法和剑理。似缓似快，既在速度上使人难以把\n"+
        "握，而剑锋震颤，像灵蛇的舌头般予人随时可改变攻击方向的感觉。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「空」只能在战斗中使用!\n");
    
    msg=HIY"$w"+HIY+"黄芒横空，剑光烁闪，连环十多剑，每剑均令$n"+HIY+"不得不全神应付，每剑均是朴实古\n"+
        "拙，偏又有空山灵雨、轻盈飘逸的感觉。且招招均针对$n"+HIY+"的身形变化，似是把$n"+HIY+"看通看\n"+
        "透一般！\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「空」只能在战斗中使用!\n");
    
    msg=HIG"$N"+HIG+"那秀美出尘的玉容仍是恬静闲雅，不会像一般人在狠拚时睁眉突目，咬牙切齿。\n"+
        "却是已经进入无人无我的通明境界，$w"+HIG+"来去无痕，式式均是妙至毫巅的杰作。看似随\n"+
        "意，但无不是最能针对敌手的高明剑招。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    me->set("apply_points",0);
    me->set_temp("perform_busy",time());
    return 1;
}
