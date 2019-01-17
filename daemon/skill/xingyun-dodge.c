//行云九步。

#include <ansi.h>
inherit SKILL;
string *dir=({"乾","坤","震","巽","坎","离","亘","兑"});
string *num=({"几次","几个","没怎么"});
string *do1=({"闪晃","移晃"});
string *do2=({"躲开","闪开","避开"});

mapping action = ([
         "action" : "$n身形变换无常，几个闪晃，从"+YEL"[乾]"NOR+"位晃到了"+YEL"[坤]"NOR"位，闪开了$n的攻击。"
]);


mapping query_action(object me)
{
     int i,j;
     i=random(8);
     j=random(8-i);
     action["action"]="$n身形变换无常，"+num[random(sizeof(num))]+
	do1[random(sizeof(do1))]+",从"+YEL+dir[i]+NOR+"位晃到了"+
	YEL+dir[j]+NOR+"位，"+do2[random(sizeof(do2))]+"了$N的进攻。\n";
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
	return "dodge";
}
string query_base()
{
	return "dodge";
}

string *query_perform()
{
   return ({"nitian"});
}

int query_dodge(object me)
{
	return 50;
}