//天狼刀法
//低级武功
inherit SKILL;
#include <ansi.h>

mapping *action=({
 ([ "action":"$N掌中$w一错，一招「饿狼扑食」幻出漫天刀影拢向$n的$l！",
    "apply_factor": 2,
    "name" : "饿狼扑食",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N展身虚步，提腰跃落，一招「月夜狼影」，刀锋一卷，拦腰斩向$n！",
    "apply_factor": 3,
    "name" : "月夜狼影",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N挥舞$w，使出一招「群狼分尸」，上劈下撩，左挡右开，齐齐罩向$n！",
    "apply_factor": 4,
    "name" : "群狼分尸",
    "damage_type":"割伤",
  ]),
  ([ "action":"$N使出一招「天狼袭月」，刀光一闪，斜斜劈向$n的$l！",
    "apply_factor": 5,
    "name" : "天狼袭月",
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
   return action[random(sizeof(action))];
 

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

int valid_learn(object me)
{
	object weapon;
	if(!objectp(weapon=me->query_temp("weapon"))||
		weapon->query("skill_type")!="blade")
			return notify_fail("手中无刀，如何学习天狼刀法？\n");
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
  
  return 50;
}