#include <ansi.h>
inherit SSERVER;

void check(object me);
void remove_effect(object me);

int perform(object me,object victim)
{
        int skill;
        int sword_skill,qixiu_skill;
        
        skill = me->query_skill("tianmo-dafa",1);
        if( skill > 250 ) skill=250;
        sword_skill= me->query_skill("dagger",1);
        qixiu_skill= me->query_skill("tianmo-zhan",1);
                       
        if(me->query("apply_points")<=0)
        return notify_fail("凭你目前的气势无法施展「天魔凌霄斩」!\n");
        if(me->query("max_force")<1500)
        return notify_fail("你的内力修为太低了！\n");              
        if( skill < 160 )  return notify_fail("你的天魔大法修为不够。\n");
        if( sword_skill < 160 )  return notify_fail("你的基本匕法未够纯熟。\n");
        if( qixiu_skill < 160 )  return notify_fail("你的天魔斩未够纯熟。\n");
                
        if( me->query_temp("actionp_hit/lingxiao") ) 
          {remove_effect(me);return 1;}
                          
        if( time()-(int)me->query_temp("perform_busy") < 10 )
                return notify_fail("你现在真气不纯！\n");  
        
        me->add("force", -skill);
        message_vision(HIR "$N"+HIR+"催动天魔大法，身型急转，足不沾地，有如鬼魅般飘拂不定。\n" NOR, me);
        me->set_temp("actionp_hit/lingxiao", 1);
        me->set_temp("lingxiao_time",skill/5);
                   
        call_out("check", 1, me);
        return 1;
}


void check(object me)
{       
        object weapon;
         if(!me)//如果没有物件 me，例如me quit了，则返回，不做任何事
        return;
       
        weapon=me->query_temp("weapon");
        if ( !weapon||weapon->query("skill_type") != "dagger" ) 
                 remove_effect(me);
         else if(me->query_temp("lingxiao_time")<1)
             remove_effect(me);                 
         else {  me->add_temp("lingxiao_time",-1);
                call_out("check", 1, me);
              }
                     
}


void remove_effect(object me)
{
        if(!me) return;//如果没有物件 me，例如me quit了，则返回，不做任何事
        if(!me->query_temp("actionp_hit/lingxiao"))
        return;
        me->delete_temp("actionp_hit/lingxiao");
        me->set_temp("perform_busy",time());
        tell_object(me, HIG"\n你将天魔大法收回丹田。\n\n"NOR);
        return;
}
