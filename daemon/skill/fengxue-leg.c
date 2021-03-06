// 弈剑派。
//中级。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N纵身跃起，一招「大雪纷飞」，双腿以排山倒海之势踢向$n的$l！",
        "apply_factor": 2,
        "name": "大雪纷飞",
       "damage_type": "瘀伤"
]),

([  "action": "$N身形一蹲，一式「风扫落叶」，左腿为轴,右腿扫向$n的双腿！",
        "apply_factor": 3,
        "name": "风扫落叶",
        "damage_type": "瘀伤"
]),

([      "action": "$N使出一式「雪花飘飘」，$n的周身大穴尽在双腿的笼罩之下。",
        "apply_factor": 4,
        "name": "雪花飘飘",
        "damage_type": "瘀伤"
]),

([  "action": "只见$N向后一仰，一招「雪峰撑天」，双手支地而起,双腿踢向$n的面门，真是诡异无比。",
        "apply_factor": 5,
        "name": "雪峰撑天",
        "damage_type": "瘀伤"
]),

([  "action": "$N一式「风转云幻」跃到$n眼前，双手一晃$n的眼神，右膝撞向$n的小腹！",
        "apply_factor": 6,
        "name": "风转云幻",
        "damage_type": "瘀伤"
]),

([  "action": "$N一招「天风浩荡」，朝$n就是一腿。这一腿仿佛充满天地，使$n挡无可挡，避无可避！",
        "apply_factor": 7,
        "name": "天风浩荡",
        "damage_type": "瘀伤"
]),
});

string *parry_weapon=({

"$N纵身跃起，双脚连环朝$n手腕踢去，$n连忙收回$v，后退开来！\n",
"$N蹲下身右腿一扫，一片沙尘朝$n扑去，$n一惊，连忙收回$v退后几步！\n",
"$N身子盘旋上升，双脚连环踢出，啪啪几下踢开了$n的$v。\n",
"$N右脚踢开$n的$v，身子一转，左脚又朝$n的头部踢去，$n一个侧身，收回$v退了开来！\n"

});

string *parry_hand=({

"$N纵身跃起，双脚连环朝$n手腕踢去，$n连忙后退开来。\n",
"$N蹲下身右腿一扫，一片沙尘朝$n扑去，$n一惊，连忙退后几步！\n",
"$N身子盘旋上升，双脚连环踢出，啪啪几下格开了$n的进攻。\n",
"$N右脚踢开$n的进攻，身子一转，左脚又朝$n的头部踢去，$n一个侧身，退了开来！\n"

});

string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

}

mapping query_action(object me)  
{
        return action[random(sizeof(action))];
}
mapping *query_all_action(object me)
{
return action;	
}
int valid_learn(object me)
{
     return 1;  
        
       
}

int practice_skill(object me)
{
   return 1;
}



string query_type() 
{
	return "hand";
}

string query_base()
{
	return "leg";
}

mapping query_select_action(int i)
{
   if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}

string *query_perform()
{
  return ({"jifeng"});
}

int skill_damage(object me,object victim)
{

  return 100;
}

