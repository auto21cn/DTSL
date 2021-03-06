// 千变铜萧
//终极武功。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N的$w画出一个又一个的圈子，每个旋圈，铜萧的真气均会随之增聚。\n"+
                  "两眼则一瞬不瞬的瞧看$n，神情傲视天下，正是一招「铜萧初变」！ ",
        "apply_factor": 2,
        "name" : "铜萧初变",
        "damage_type": "瘀伤"
]),

([  "action": "$N脚踏奇步，身形不断变化，同时口中发出啸声，一阵魔幻般的萧音油然自生，\n"+
              "让身在局中的$n如痴如醉，身形也开始露出破绽。",
        "apply_factor": 5,
        "name" : "萧声悦起",
        "damage_type": "瘀伤"
]),

([      "action": "$N凌空虚踏，摄人心魄的凭空升起，$w笼罩$n的头顶，轻轻晃动，\n"+
                  "角度顿时刁钻古怪起来。端是变化万千，魔门秘技，果然匪夷所思。",
        "apply_factor": 10,
        "name" : "千变凌头",
        "damage_type": "瘀伤"
]),

([  "action": "$N把横在胸前的$w缓缓推出，真气在$w中澎湃跃动，含而不吐，带出一股震\n"+
              "撼天下的气势，$n整个心神都被$w吸引，眼中的$w越变越大，势不可挡。",
        "apply_factor": 7,
        "name" : "萧指天下",
        "damage_type": "震伤"
]),

});

string *parry_weapon=({

"$N灌注真力于$w之上，画出数个圆圈，以古怪的招数架住了$n的$v！\n",
"$N手中$w配合口中的魔音，几个简单的招式朝$n的$v挡去！\n",
"$N手中的$w如灵蛇一般，正好挡住$n的$v。\n",
"$N纵身越起，$w如长了眼睛一般，正好挡住$n的$v！\n"

});

string *parry_hand=({

"$N手中的$w如同鬼魅一般，刺向$n的手腕，$n连忙退开，惊出一身冷汗！\n",
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
        object weapon;
        
       
        weapon=me->query_temp("weapon");
        if(!weapon)
         return notify_fail("不拿武器如何学习千变铜萧？\n");
        if(weapon->query("skill_type")!="sword")
         return notify_fail("你拿得武器不对。\n");
        
     return 1;  
        
       
}

int practice_skill(object me)
{
      
object weapon;
        
        weapon=me->query_temp("weapon");
        if(!weapon)
         return notify_fail("不拿武器如何练习千变铜萧？\n");
        if(weapon->query("skill_type")!="sword")
         return notify_fail("你拿得武器不对。\n");
      
     return 1; 
}

string *query_perform()
{
	return ({"wanhuan"});    
}


string query_type()  
{
	return "sword";
}

string query_base()
{
	return "sword";
}

mapping query_select_action(int i)
{
   if((i)>sizeof(action))
		return 0;
	else return action[i-1];
}
int skill_damage(object me,object victim)
{
  
  return 200;
}