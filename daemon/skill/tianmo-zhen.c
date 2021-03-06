//天魔阵。


inherit SKILL;

#include <ansi.h>

string query_type()
{
  return "literate";
}

int valid_learn(object me)
{
    return 1;
}

object offensive_target(object me)
{
	int sz;
	object *enemy,target;

	enemy = me->query_enemy();
	if( !enemy || !arrayp(enemy) ) return 0;

	sz = sizeof(enemy);
	if( sz > 4 ) sz = 4;

	if( sz > 0 ){
	  target=enemy[random(sz)];
	  return target;
	}
	else return 0;
}

int form_array(object me)
{
   object *t,target;
   int i,fight_flag=0,damage;
   
   t=me->query_team();
   t=t-({0});
   if(sizeof(t)!=4) return notify_fail("要施展天魔阵只能是四个人！\n");
   
   if(time()-me->query_temp("form_busy")<10)
   return notify_fail("你真气不足，无法施展天魔阵！\n");
   
   for(i=0;i<sizeof(t);i++)
    if(objectp(t[i])){
     if(environment(t[i])!=environment(me))
      return notify_fail("有人不和你站在一起！\n");
     if(t[i]->query_skill("tianmo-zhen",1)<160)
      return notify_fail(t[i]->name()+"天魔阵修为太低了！\n");
    }
   target=offensive_target(me);
   if(!target)
   return notify_fail("你没有战斗的目标！\n");
   
   if(me->is_killing(target->query("id")))
    fight_flag=1;
   message_vision(HIR"\n$N"+HIR+"一声长啸：「天魔阵」！顿时四周好似腥风血雨一般！\n"NOR,me);
   for(i=0;i<sizeof(t);i++){
      if(!t[i]->is_fighting(target)){
        if(fight_flag) {t[i]->kill_ob(target);target->kill_ob(t[i]);}
        else {t[i]->fight_ob(target);target->fight_ob(t[i]);}
      }
      t[i]->set_temp("form_busy",time());
      damage=t[i]->query("apply_points");
      t[i]->add_temp("apply/damage",damage);
      COMBAT_D->do_attack(t[i],target,t[i]->query_temp("weapon"),0,2);
      t[i]->add_temp("apply/damage",-damage);
   }
   
   return 1;
} 