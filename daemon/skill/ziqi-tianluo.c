// 紫气天罗

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N两手高举，如大鹏展翅，十指伸张，招数怪异地朝$n的$l处抓去!",
        "apply_factor": 2,
        "name" : "招数",
       "damage_type": "瘀伤"
]),

([  "action": "$N退出丈许远近后回掠过来，侧击$n，双方各以精奥手法硬拚一招！",
        "apply_factor": 2,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

([      "action": "$N不怒反笑，两掌穿花蝴蝶般幻起漫空掌影，随著前踏的步法，铺天盖地的往$n攻去！",
        "apply_factor": 2,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

([  "action": "$N脚踩奇步，脸泛紫气，飘移不定的几个假身后，抢往$n左侧，左手疾劈$n的$l！",
        "apply_factor": 2,
        "name" : "招数",
        "damage_type": "瘀伤"
]),

});


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
