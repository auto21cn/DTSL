//血战十式。李靖。
inherit SKILL;
#include <ansi.h>

mapping *action = ({
([ "action":HIR"$N手中$w一横，隐然有一股将军之式，封住了$n的所有招式，正是一招[两军对垒]！"NOR,
    "apply_factor": 5,
    "name" : "招数",
    "damage_type":"砍伤",
  ]),
 ([ "action":HIR"$N手中$w一闪，欺身上前，$w刷地一声砍了过去，正是一招[烽芒毕露]！"NOR,
    "apply_factor": 5,
    "name" : "招数",
    "damage_type":"砍伤",
  ]),
  ([ "action":HIR"$N身行一晃，闪到了$n身后，手中的$w猛地挥出，正是一招[轻骑突出]！"NOR,
    "apply_factor": 5,
    "name" : "招数",
    "damage_type":"砍伤",
  ]),
  ([ "action":HIR"$N手中$w连劈数下，身行向前，手中$w一招[探囊取物]直砍向$n的$l！"NOR,
    "apply_factor": 5,
    "name" : "招数",
    "damage_type":"砍伤",
  ]),
  ([ "action":HIR"$N纵身跃起，手中的$w竖直劈下，正是一招[一战功成]砍向$n的$l！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]),
  ([ "action":HIR"$N手中$w一挥，挡开了$n的进攻，同时一招[批亢捣虚]朝$n的$l处砍去！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]),  
   ([ "action":HIR"$N手中的$w四方闪动，闪出一片刀影，正是一招[兵无常势]砍向$n的$l！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]), 
   ([ "action":HIR"$N猛地侧过身子，手中的$w直接砍向$n的$l,正是一招[死生存亡]！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]), 
	([ "action":HIR"$N手中的$w左挡右格，尽数挡开了$n的进攻，正是一招[强而避之]！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]), 
	([ "action":HIR"$N手中的$w挥出，隐有风雷之声，合有帝王之气势，一招[君临天下]砍向$n的$l！"NOR,
     "apply_factor": 5,
    "name" : "招数",
     "damage_type":"砍伤",
    ]), 
 });   


int valid_learn(object me)
{
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


mapping query_action(object me, object weapon)
{
   return action[random(sizeof(action))];

}

string *query_perform()
{
	return ({"bajue"});
}
string query_type()
{
	return "blade";
}
string query_base()
{
	return "blade";
}
mapping query_select_action(int i)
{
	if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}
