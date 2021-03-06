
#include <ansi.h>
inherit SSERVER;
/*心法执行函数
  统一放在 /daemon/skill/exec/ 下。
*/
int execute(object me,object victim)
{
  
  int armor;
  string msg;
  
  if(victim!=me)
  return notify_fail("你不能对别人使用这个心法。\n");
  
  victim=offensive_target(me);
  
  if( me->query_skill("sashoufa",1)&&
      (me->query_skill("sashoufa",1)<190
      ||!me->query("execute_quest/xinyoulingxi"))
    )
  return notify_fail("你的撒手法还不到家，无法施展「静守」！\n");
  if(me->query_skill("siguanfa",1)&&
      (me->query_skill("siguanfa",1)<190
      ||!me->query("execute_quest/jianxintongming"))
    )
  return notify_fail("你的死关法还不到家，无法施展「静守」！\n");
  
  if(me->query_temp("execute_jingshou"))
  return notify_fail("你正在使用「静守」！\n");
  if(time()-me->query_temp("execute_jingshou_busy")<15)
  return notify_fail("你无法连续施展「静守」。\n");  
  if(me->query("force")<200)
  return notify_fail("你的内力不足！\n");
  
  me->add("force",-200);
  if(me->query_skill("siguanfa",1))
  armor=me->query_skill("siguanfa",1)*2;
  else
  armor=me->query_skill("sashoufa",1)*2;
   
  msg=HIY"\n$N"+HIY+"默念慈航剑典秘诀，立刻处于守势，周身似乎环绕起一道气墙！\n"NOR;
  
     message_vision(msg,me);
 
  me->set_temp("execute_jingshou",1);
  me->set_temp("no_eff_combat",1);
  me->add_temp("apply/armor",armor);
  
  call_out("execute2",armor/(2*8),me,armor);
  
  return 1;
}

void execute2(object me,int armor)
{
   if(!me)
    return;
    
   message_vision("\n$N收回了慈航剑典神功。\n",me);
   
   me->delete_temp("execute_jingshou");
   me->delete_temp("no_eff_combat");
   me->add_temp("apply/armor",-armor);
   me->set_temp("execute_jingshou_busy",time());
   
   return;
}
