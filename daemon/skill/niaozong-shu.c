// 鸟纵术。

#include <ansi.h>
inherit SKILL;


mapping *action = ({
([      "action" : "$n身形微微一晃，宛如大鸟般跃上高空，闪开了$N的攻击。"
]),
([      "action" : "$n身行不住地晃动,十分灵巧地闪开了$N的进攻。"
]),
([      "action" : "$n身体突然一横，犹如铁板桥一样，旋转着躲开了$N的进攻!"
]),
([      "action" : "$n身形一晃，宛如大鸟横空，轻轻落到了$N的身后。"
])

});

mapping query_action(object me)
{
	

	return action[random(sizeof(action))];
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
	return 90;
}