//宋家剑法.
//中级-->终极武功。

inherit SKILL;
#include <ansi.h>

mapping *action=({
  ([ "action":"$N身法沉稳，不露一丝破绽，一招「青松迎客」刺向$n的$l！",
    "apply_factor": 2,
    "name" : "青松迎客", 
    "damage_type":"刺伤",
  ]),
 ([ "action":"$N手中$w一横，运气于$w之上，一招「南岭回风」突然刺向$n的$l！",
    "apply_factor": 5,
    "name" : "南岭回风",
    "damage_type":"刺伤",
  ]),
  ([ "action":"$N身形飘忽不定，四处游走，猛地一招「游龙乍现」刺向$n的$l！",
    "apply_factor": 10,
    "name" : "游龙乍现",
    "damage_type":"刺伤",
  ]),
  ([ "action":"$N手中$w化作一声龙吟，只听‘刷’地一声，$w已朝$n的$l处刺去，正是一招「南岭升龙」！",
    "apply_factor": 7,
    "name" : "南岭升龙",
    "damage_type":"刺伤",
  ])});   

string *parry_weapon=({

"$N灌注真力于$w之上，以普通而平凡的招数架住了$n的$v！\n",
"$N手中$w出招大开大阖，几个简单的招式朝$n的$v挡去！\n",
"$N长啸一声，手中的$w划了一个圆弧，正好挡住$n的$v。\n",
"$N手中的$w奋力一挑，以四两拨千斤、借力打力之巧架开$n的$v！\n"

});

string *parry_hand=({

"$N微微一笑：手中的$w刷地一声刺向$n的手腕，$n连忙退开，惊出一身冷汗！\n",
"$N手中的$w一横，宛如铁索一般挡住了$n的攻击！\n",
"$N一挥手中的$w，一道气劲挡住了$n的攻势。\n",
"$N手中的$w如同灵蛇一般，从匪夷所思的角度封住了$n的进攻！\n"

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
	return "sword";
}
string query_base()  
{
	return "sword";
}

string *query_perform()
{
	return ({"dilie"});    
}

int valid_learn(object me)
{
        object weapon;
        if(!objectp(weapon=me->query_temp("weapon")))
           return notify_fail("不拿武器如何学习宋家剑法？\n");
        if(weapon->query("skill_type")!="sword")
           return notify_fail("不拿剑如何学习宋家剑法？\n");
	return 1;
}
int practice_skill(object me)  
{
  object weapon;
        if(!objectp(weapon=me->query_temp("weapon")))
           return notify_fail("不拿武器如何练习宋家剑法？\n");
        if(weapon->query("skill_type")!="sword")
           return notify_fail("不拿剑如何练习宋家剑法？\n");
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
  if(me->query("perform_quest/dilie"))
  return 90;
  return 50;
}

int skill_parry(object me,object victim)
{
  if(me->query("perform_quest/dilie"))
  return 90;
  return 50;
}