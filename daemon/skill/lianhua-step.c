//莲花步法。静念禅院轻功.

#include <ansi.h>
inherit SKILL;


mapping *action = ({
([      "action" : "$n气定神闲，有若清风白云，身行一晃，一招「飞云渡天」躲开了$N的攻击。"
]),
([      "action" : "$n看准$N的位置，身法如晴空之中的白云飘向一旁，正是一招「清云无常」。"
]),
([      "action" : "$n神轻气闲，身行只是微微一动,便闪开了$N的攻势，正是一招「淡云悠悠」！"
]),
([      "action" : "$n身行左闪右晃，躲开了$N的攻击，如同数个幻影一般，正是一招「流云无常」。"
])

});

mapping query_action(object me)
{
	

	return action[random(sizeof(action))];
}


int valid_learn(object me)
{
       if((int)me->query("PKS",1)>=5)
		   return notify_fail("你感到自身罪孽深重，不能继续学习「莲花步法」了！\n");

	   return 1;
}



int practice_skill(object me)
{
     if((int)me->query("PKS",1)>=5)
     return notify_fail("你感到自身罪孽深重，不能继续练习「莲花步法」了！\n");
	
	return 1;
}

string query_type()
{
	return "dodge";
}
string query_base()
{
	return "dodge";
}

int query_dodge(object me)
{
	
	return 70;
	
}