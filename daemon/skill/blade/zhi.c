//花间十二支。
//折花百式pfm.
#include <ansi.h>

inherit SSERVER;

#define REDUCE_DEX -150


int perform(object me,object target)
{ 
    object weapon;
    int damage;
    string msg;
    
    weapon=me->query_temp("weapon");
    
    if(!target)
    if(!objectp(target=offensive_target(me)))
    return notify_fail("目前你没有攻击的目标！\n");
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用！\n");
   if(!weapon)
    return notify_fail("不拿武器，如何使用「花间十二支」？\n");
   if(weapon->query("skill_type")!="blade")
   return notify_fail("你使用的武器类型不对！\n");
   if(weapon->query("flag")==1)
		return notify_fail("断掉的兵刃如何使用？\n");
    if(!me->query_skill("zhehua-baishi"))
    return notify_fail("不学「折花百式」如何使用「花间十二支」？\n");
    if((int)me->query("max_force")<1500)
    return notify_fail("你的内力修为太低了!\n");
    if((int)me->query_skill("blade",1)<160)
    return notify_fail("你的基本刀法太差了！\n");
    if((int)me->query_skill("zhehua-baishi",1)<160)
    return notify_fail("你的折花百式还不到家！\n");
    if(me->query_skill("huachan",1)<160)
    return notify_fail("你的画禅修为太低了！\n");
    if(me->query_skill("flower-force",1)<150)
    return notify_fail("你的飞花流水修为太低了！\n");
    if(me->query("execute_quest/busiyin"))
    return notify_fail("领会了不死印，无法再施展「花间十二支」！\n");
    
    if(!me->query("perform_quest/zhi")
      &&time()-me->query_temp("perform_busy")<5)
      return notify_fail("连续施展「花间十二支」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    if( (me->query("perform_quest/zhi")||me->query("perform_quest/zhi_fail") )
      &&time()-me->query_temp("perform_busy")<10)
      return notify_fail("连续施展「花间十二支」需要深厚的先天真气支持，你修为不够，如何能行？\n");
    
    if(me->query("apply_points")<=0)
    return notify_fail("凭你目前的气势无法施展「花间十二支」！\n");
    
    damage=me->query("apply_points");
    
    if(me->query("perform_quest/zhi_fail"))
    damage=damage*3/4;
    else
    if(!me->query("perform_quest/zhi"))
    damage=damage/2;
    else
    me->set("apply_points",0);
    
    msg=HIC"一霎眼间，$N"+HIC+"倏然不见了。一阵风吹过，$n"+HIC+"的招式带起微风，造成急卷的气流，$N"+HIC+"轻如落叶，\n"+
        "却已飘到$n"+HIC+"背后，那天地间无略可遁，无地可活，无处可逃的一堵一击，却依然如风吹过，\n"+
        "困不住$N"+HIC+"。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=HIM"$N"+HIM+"的$w"+HIM+"缓缓张开，如同鲜花怒放，虽招招杀着，表面看去却是潇洒优美，于紧迫激烈中隐\n"+
        "含一种闲逸的超然意味，就像为美人绘像，随意敷采，却精彩纷呈，深得画道之旨。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=WHT"$N"+WHT+"全身化作一片扇影翩翩起舞，只见$N"+WHT+"越舞越急，舞到最后，带的周围空气如同漫天风雪，\n"+
        "都似一条无形的风线，串连在一起，而$N"+WHT+"成为那旋风的中心，那千百朵雪花飞舞，舒卷住人\n"+
        "影，然而那$w"+WHT+"始终未抚出。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=HIY"$N"+HIY+"身形舞动，$w"+HIY+"奇迹般耀眼生花，如同月光照在扇骨上，好似太阳一般亮，月光怎会\n"+
        "如此灿亮眩烁？暗香流动，月静，无声。$N"+HIY+"好似在月下，月芒披在他肩上，如静柔的披凤。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    if(!me->query("perform_quest/zhi")){
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
    
    damage=damage*me->query("perform_quest/zhi_damage")/90;
    
    msg=YEL"$N"+YEL+"的$w"+YEL+"不住变幻，西风下团团扇影围住$n"+YEL+"，尽显冷傲高洁。扇法傲霜怒放，凌寒不凋，\n"+
        "正如美人扇上的美人，以墨色显示出鲜艳夺目的光彩。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=HIM"$w"+HIM+"转动，$N"+HIM+"如同傲雪凌霜，$N"+HIM+"的招数亦如美人声色般变幻，一时流出冰清玉洁不同流俗\n"+
        "的气质，其奇招异法充斥不与寻常招数争斗的兀傲之气，心意流露的宛如书般清楚。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=HIG"$N"+HIG+"内力到处，$w"+HIG+"片片洒落，轻风吹翠竹般的片片$w"+HIG+"，轻轻震动发出音韵流畅，情味悠长，\n"+
        "$n"+HIG+"心神受制，由如竹中游荡，不由兴起一股向轻竹般的$w"+HIG+"膜拜的欲望。全然不顾激射来的\n"+
         "碎片！\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    msg=HIY"空间变化，散开的$w"+HIY+"中美女面容突然重现在$n"+HIY+"的眼前，端庄的气质，恍如冰肌玉洁，\n"+
        "亭亭玉立的少女，足以令人为之倾倒，$N"+HIY+"身形和$w"+HIY+"中美人面貌遥相呼应。\n"NOR;
    
    COMBAT_D->do_perform_attack(damage,REDUCE_DEX,msg,me,target,weapon,0,2);
    
    if(!me->is_fighting())
    return notify_fail("「花间十二支」只能在战斗中使用!\n");
    
    if(random(100)>70){
    	msg="\n$n心神受制，心神遁入扇花中，如同做梦一般，再无半点气势可言！\n";
        target->start_busy(2);
       if(random(100)>80){
        msg+="\n$N步法变幻，$n如同身陷花影，身形慢慢变慢，凝滞起来！\n";
        target->start_busy(4);
        if(random(100)>90){
         msg+="\n$N身在花间舞动，如同花中之魂，遥遥制住$n！\n";
         target->start_busy(6);  
           if(random(100)>95){
             msg+="\n"+weapon->name()+"落下，画上的美人如花，慢慢凋谢，$n不由发出侬今葬花人笑痴，\n"+
                  "他年葬侬知是谁的感叹！\n";
             target->start_busy(8); 
           }
        }
      }
      
      message_vision(msg,me,target);
    }
        
   me->set_temp("perform_busy",time());
   
 return 1;   
  
} 

