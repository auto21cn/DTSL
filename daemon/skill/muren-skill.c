// 木头人的技能
//技能等级分为 低 中 高 三部分。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N体内机关牵引，动作灵活超乎常人，猛地一拳朝$n的$l处打去！",
        "apply_factor": 5,
        "name" : "招数",
       "damage_type": "砸伤"
]),

([  "action": "$N体内嘎吱嘎吱几声连响，突见$N伸长数寸，在$n不防备下打来！",
        "apply_factor": 5,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

([      "action": "$N上身突然后倾，只听嘎吱一声，双脚如旋风一般朝$n踢来！",
        "apply_factor": 5,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

([  "action": "$N突然犹如发疯一样，双拳拼命朝$n砸去，下面双脚也是不停的进攻！",
        "apply_factor": 5,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

});

mapping query_action(object me,object victim)
{
   return action[random(sizeof(action))];
}


string *query_perform()
{
	return ({"suimu"});   
}


string query_type() 
{
	return "hand";
}

string query_base()
{
	return "strike";
}

mapping query_select_action(int i)
{
   if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}


int skill_damage(object me,object victim)
{
  if(me->query("target_lev")=="low")
  return 10;
  else
  if(me->query("target_lev")=="mid")
  return 50;
  else
  return 70;
  
}
