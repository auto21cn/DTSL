// 破玉拳。宋家堡武功。
// 低等级

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N左拳下防，右拳猛地挥出，一招「开门见山」打向$n的$l!",
        "apply_factor": 2,
        "name" : "开门见山",
       "damage_type": "瘀伤"
]),

([  "action": "$N身行不住变化，左拳先是虚晃一下，右拳再猛地挥出，一招「声东击西」打向$n的$l!",
        "apply_factor": 3,
        "name" : "声东击西",
        "damage_type": "瘀伤"
]),

([      "action": "$N双拳打出一片拳影，一招「流星暴雨」击向$n的$l处！",
        "apply_factor": 4,
        "name" : "流星暴雨",
        "damage_type": "瘀伤"
]),

([  "action": "$N双拳十字交叉，攻守兼备，一声清啸，一招「破玉十字」打向$n的$l!",
        "apply_factor": 5,
        "name" : "破玉十字",
        "damage_type": "瘀伤"
]),

});

string *parry_weapon=({

"只见$N不顾$n的$v，架住了$n的手腕，同时手肘向前一撞，$n不得不后退开来。\n",
"$N完全不顾$n的$v，反而以更快的速度打向$n的$l，好象围魏救赵般化解了$n的进攻。\n",
"$N双拳十字交叉，攻守兼备，封住了$n的进攻。\n",
"$N双拳打出一片拳影，化解了$n的进攻！\n"

});

string *parry_hand=({

"$N的手掌迎上$n的进攻，只听碰地一声，双方各退后几步。\n",
"$N拳法错乱，如同万千幻影，$n见势不好，连忙后退开来！\n",
"$N招式严谨，出招丝毫不乱，轻轻一招化解了$n的进攻。\n",
"$N的拳势轻轻一带，化解了$n的进攻！\n"

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
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
            return notify_fail("空了手才能学习破玉拳。\n");
     return 1;  
        
       
}

int practice_skill(object me)
{
      object weapon;
      if(objectp(weapon=me->query_temp("weapon")))
		  return notify_fail("必须空手才可以练习破玉拳！\n");
     return 1;
}

string query_type() 
{
	return "hand";
}

string query_base()
{
	return "cuff";
}

mapping query_select_action(int i)
{
   if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}
int skill_damage(object me,object victim)
{
  
  return 60;
}
