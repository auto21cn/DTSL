//空手招架.

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N伸出手掌拍向$n",
        "dodge": 10,
        "force": 50,
		"damage":50,
        "parry" : -15,
        "damage_type": "瘀伤"
]),
([
 "action":"$N一式[黑虎掏心]掏向$n的心窝!",
 "dodge":15,
 "force":50,
 "parry":20,
 "damage_type": "瘀伤"
]),
([
 "action":"$N蹦了起来,一脚踹向$n的头部!",
 "dodge":15,
 "force":50,
 "parry":20,
 "damage_type": "瘀伤"
])


});





string query_skill_name(int level)
{
        
}

mapping query_action(object me)
{
        return action[random(sizeof(action))];
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
	return "base";
}

string perform_action_file(string action)
{
	return __DIR__"hand/"+action;
}