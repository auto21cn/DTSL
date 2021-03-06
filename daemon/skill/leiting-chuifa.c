//【雷霆锤法】leiting-chuifa.c
//中级-->终极武功。

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([ "action":"$N跃空而起,手中$w一转，一式「五雷轰顶」卷着一股强劲的风力砸向$n！",
    "apply_factor": 2,
    "name" : "五雷轰顶",
    "damage_type":"砸伤",
  ]),
 ([ "action":"$N双手一震，一式「雷神击鼓」，手中$w夹带着闷雷般的响声，从上至下向$n砸了过去！",
    "apply_factor": 5,
    "name" : "雷神击鼓",
    "damage_type":"砸伤",
  ]),
  ([ "action":"$N身走轻灵，一式「雷动九天」手中$w忽上忽下，令人捉摸不清去路，就在$n一恍惚间，\n"+
              "“唰”地砸向$n的$l！",
    "apply_factor": 10,
    "name" : "雷动九天",
    "damage_type":"震伤",
  ]),
  ([ "action":"$N将$w高举过肩，蓄紧力发，对准$n的$l发出一招「雷霆千钧」,这一下又急又猛。",
    "apply_factor": 7,
    "name" : "雷霆千钧",
    "damage_type":"砸伤",
  ]),
 });   

string *parry_weapon=({

"$N大喝一声，手中的$w朝$n的$v砸去，$n一惊之下，连忙退后开来。\n",
"$N完全不顾忌$n的$v，挥舞手中的$w呼的一声朝$n砸去！$n连忙撤回$v，后退开来。\n",
"$N将$w挡在胸前，正好挡住$n的$v，震得$n双臂发麻！\n",
"$N的$w直朝$n的下盘砸去，$n无奈之下，只好收回了$v。\n"

});

string *parry_hand=({

"$N的$w忽然轻灵起来，朝$n的手掌砸去，$n无奈之下只好后退几步。\n",
"$N一挥手中的$w，$w宛如铁板一般，横在了两人之间，$n的进攻之力也化为乌有！\n",
"$N大喝一声，手中的$w挥舞起来，轻轻带过了$n的进攻。\n",
"$N的$w轻轻一带，化解了$n的进攻！\n"

});


string query_parry_action(object me,object victim)
{
   if(victim->query_temp("weapon"))
    return parry_weapon[random(sizeof(parry_weapon))];
   return parry_hand[random(sizeof(parry_hand))];

}

int valid_learn(object me)
{
     object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "hammer")
                return notify_fail("你使用的武器不对。\n");
     return 1;  

}

int practice_skill(object me)
{
  object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "hammer")
                return notify_fail("你使用的武器不对。\n");
 
 return 1;  


}


mapping query_action(object me, object weapon)
{
   return action[random(sizeof(action))];

}
mapping *query_all_action(object me)
{
return action;	
}

string *query_perform()
{
	return ({"pili","honglei"});
}
string query_type()
{
	return "hammer";
}
string query_base()
{
	return "hammer";
}
mapping query_select_action(int i)
{
	if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}

int skill_damage(object me,object victim)
{
if(me->query("perform_quest/pili")) 
  return 200;
else
	return 80;
}
