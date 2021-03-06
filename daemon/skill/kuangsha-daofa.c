//狂沙刀法
//中级-->终极武功。

inherit SKILL;
#include <ansi.h>

mapping *action=({
 ([ "action":"$N腾身而起，每一个旋身，都带起一阵充满节奏感和劲力的呼啸声，左鞘右刀，交又织出锋芒雷
射，攻守兼备的罩网,好一个「旋字诀」！",
    "apply_factor": 2,
    "name" : "旋字诀",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N一招「吹字诀」奇异的劲气，以$N为中心像沙漠刮起的狂暴风沙般，随着$N的迫近，以雷霆万
钧之势往$n袭去！",
    "apply_factor": 5,
    "name" : "吹字诀",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N一声长啸．刀法一变．幻出流沙滚动般的刀浪，重重往$n攻去，正是狂沙五诀中的「滚沙诀」！",
    "apply_factor": 10,
    "name" : "滚沙诀",
    "damage_type":"割伤",
  ]),
  ([ "action":"$w在虚空画出一道充满旋卷味道、波浪般起伏的轨迹，变化无穷的朝$n“卷”过来！",
    "apply_factor": 7,
    "name" : "卷字诀",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N往前虎扑，$w依循一道弯旋的弧线轨迹，往$n斩去,好一招 「破字诀」！",
    "apply_factor": 6,
    "name" : "破字诀",
    "damage_type":"割伤",
  ]),

});   

string *parry_weapon=({

"$N手中$w专走险路，完全不顾及自己的安全，猛地架住了$n的$v！\n",
"$N如同拼命一般，$w向前一架，架住了$n的$v！\n",
"$N低喝一声，手中$w一拨一挑，已然架住了$n的$v！\n",
"$N手中$w周身一转，舞出一道白光围住自己，将$n的$v挡在外面！\n"

});

string *parry_hand=({

"$N提起$w一推，卷起一阵旋风，$n不得不收回招式后退开来。\n",
"$N反功为守，提起$w横腰朝$n斩去，$n不得不收回招式，跃身躲开。\n",
"$N一刀划右，一刀划左，一刀直劈，唰唰唰三刀已然将$n的进攻化为乌有。\n",
"$N挥刀虚空一斩，$n的进攻不由得被牵扯过去！$n心中一惊，连忙后退开来！\n"

});

string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

}


mapping query_action(object me,object weapon)
{
   
   int i, level,temp;
	object target;
	object *enemy;

	level = me->query_skill("kuangsha-daofa",1);

	enemy = me->query_enemy();
	if(sizeof(enemy)>0)
	{
       target = enemy[random(sizeof(enemy))];

 	if ( random(10)>=7 && me->query("force")>500 ) {
		if ( me->query_skill("yanyang-dafa",1)>=200 
				&& me->query_skill("kuangsha-daofa",1)>=200 
				&& !me->query_temp("apply_at")) {
			me->set_temp("apply_at",1);
			call_out("autopfm",1,me,target);
		}
	}	
	}
      
   return action[random(sizeof(action))];
 

}
void autopfm(object me,object target)
{
	object weapon;
	int i;
	int damage;
	if(!me) 
		return;
	if(!target){
		me->delete_temp("apply_at");
		return;
	}	
	if(!me->is_fighting(target)){
		me->delete_temp("apply_at");
		return;
	}
	
	me->add("force",-50);
	if (me->query("force")<0) me->set("force",0);

	weapon = me->query_temp("weapon");	
	if(!weapon){
		me->delete_temp("apply_at");
		return;
	}
	damage=me->query("apply_points");
  
 	message_vision(HIY"\n$N"+HIY+"将手中"+weapon->query("name")+HIY"挥撒出一片耀眼的光华，$n"+HIY+"被刀光迷惑的不知所措！\n"+CYN+"$n"+CYN+"一个没留神就给$N"+CYN+"连攻了两下！"NOR,me,target);
	me->add_temp("apply/damage",damage);
  COMBAT_D->do_attack(me,target,weapon,0,1);  
  COMBAT_D->do_attack(me,target,weapon,0,1);  	
  me->add_temp("apply/damage",-damage);
  me->delete_temp("apply_at");
  	
  if(!me->is_fighting(target))
    me->delete_temp("apply_at");
  return;

}

mapping *query_all_action(object me)
{
return action;	
}

string query_type()    
{                      
	return "blade";
}
string query_base()  
{
	return "blade";
}

string *query_perform()
{
   return ({"kuangsha"});
}

int valid_learn(object me)
{

        int i = (int)me->query_skill("kuangsha-daofa", 1);
	object weapon;
        if (i>199) return notify_fail("学就只能学的这里了，剩下的要靠你自己练习了。 \n");
        if(!objectp(weapon=me->query_temp("weapon"))||
           (string)weapon->query("skill_type")!="blade")
			return notify_fail("手中无刀，如何学习狂沙刀法？\n");
	return 1;
}
int practice_skill(object me)  
{
   object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
 
 return 1;  


}

mapping query_select_action(int i)
{
	if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}

int skill_damage(object me,object victim)
{
  if(me->query("perform_quest/kuangsha"))
  return 200;
  return 80;
}

