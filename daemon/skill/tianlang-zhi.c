//天狼指
//低级武功
inherit SKILL;
#include <ansi.h>

mapping *action=({
 ([ "action":"$N手指一转一错，一招「饿狼扑食」幻出漫天指影刺向$n的$l！",
    "apply_factor": 2,
    "name" : "饿狼扑食",
    "damage_type":"刺伤",
  ]),
  ([ "action":"$N展身虚步，提腰跃落，一招「月夜狼影」，手指一转，疾风般刺向$n！",
    "apply_factor": 3,
    "name" : "月夜狼影",
    "damage_type":"刺伤",
  ]),
  ([ "action":"$N手指分点，使出一招「群狼分尸」，上刺下划，左挡右开，齐齐刺向$n！",
    "apply_factor": 4,
    "name" : "群狼分尸",
    "damage_type":"刺伤",
  ]),
  ([ "action":"$N使出一招「天狼袭月」，手指不住变换，斜斜刺向$n的$l！",
    "apply_factor": 5,
    "name" : "天狼袭月",
    "damage_type":"刺伤",
  ]),

});   


string *parry_weapon=({

"$N专走险路，完全不顾及自己的安全，拼命用手指弹开了$n的$v！\n",
"$N如同拼命一般，手指向前一刺，以攻代守逼退了$n的$v！\n",
"$N低喝一声，手指一拨一挑，已然弹开了$n的$v！\n",
"$N手指周身一转，数道指影围住自己，将$n的$v挡在外面！\n"

});

string *parry_hand=({

"$N手指挥动，卷起一阵旋风，$n不得不收回招式后退开来。\n",
"$N反功为守，手指朝$n刺去，$n不得不收回招式，跃身躲开。\n",
"$N一指划右，一指划左，一指直刺，连续三指已然将$n的进攻化为乌有。\n",
"$N右指虚空一划，$n的进攻不由得被牵扯过去！$n心中一惊，连忙后退开来！\n"

});

string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

}



mapping query_action(object me,object weapon)
{
   return action[random(sizeof(action))];
 

}
mapping *query_all_action(object me)
{
return action;	
}

string query_type()    
{                      
	return "hand";
}
string query_base()  
{
	return "finger";
}

int valid_learn(object me)
{
	object weapon;
	if(objectp(weapon=me->query_temp("weapon")))
			return notify_fail("手中拿着兵器，如何学习天狼指法？\n");
	return 1;
}
int practice_skill(object me)  
{
   object weapon;
	if(objectp(weapon=me->query_temp("weapon")))
			return notify_fail("手中拿着兵器，如何练习天狼指法？\n");
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
  
  return 50;
}