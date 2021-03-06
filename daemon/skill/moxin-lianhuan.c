//魔心莲环.
//中极武功。
inherit SKILL;
#include <ansi.h>

mapping *action=({
([ "action":"$N双掌变换，幻化出朵朵莲花形状，一招「莲花初现」朝$n的$l处打去！",
    "apply_factor": 2,
    "name" : "莲花初现",  
    "damage_type":"震伤",
  ]),
 ([ "action":"$N双掌灌注内力，低喝一声，只见一道劲气朝$n冲去！正是一招「魔心自现」！",
    "apply_factor": 5,
    "name" : "魔心自现",
    "damage_type":"震伤",
  ]),
  ([ "action":"$N高高纵起，双掌幻化莲花形状，一招「莲香扑面」朝$n的$l处打去！",
    "apply_factor": 6,
    "name" : "莲香扑面",
    "damage_type":"震伤",
  ]),
  ([ "action":"$N莲花手形突然一分为二，变化诡异，一招「魔莲双飞」朝$n的上下两路抓去！",
    "apply_factor": 8,
    "name" : "魔莲双飞",
    "damage_type":"抓伤",
  ])});  

string *parry_weapon=({

"$N一掌朝$n的$v打去，凭借强大的气劲震开了$n的$v！\n",
"$N莲花手形突然一分为二，动作毫不慌乱，封住了$n的进攻。\n",
"$N身高高纵起，双掌幻化莲花形状，封住了$n的进攻。\n",
"$N双掌变换，幻化出朵朵莲花形状，震开了$n的$v！\n"

});

string *parry_hand=({

"$N的莲花手形迎上$n的进攻，只听碰地一声，双方各退后几步。\n",
"$N莲花手形诡异，$n见势不好，连忙后退开来！\n",
"$N神情古怪，莲花手形缓缓递出，正好化解了$n的进攻。\n",
"$N和$n手掌对在一起，只听碰地一声，双方各退后几步。\n"

});

string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

} 

int valid_learn(object me)  
{
    
   
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
            return notify_fail("空了手才能学习魔心连环。\n");
    
     return 1;    


}

int practice_skill(object me)  
{
 
 if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
            return notify_fail("空了手才能练习魔心连环。\n");
            
 return 1;  


}


mapping query_action(object me,object weapon)
{
   
return action[random(sizeof(action))];  
 
}

mapping *query_all_action(object me)
{
return action;	
}

string *query_perform()
{
	return ({"feilian"}); 
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
  
  return 120;
}