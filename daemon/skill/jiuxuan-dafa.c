//九玄大法(force)

inherit FORCE;

#include <ansi.h>

int valid_learn(object me)
{       
      
	return 1;
}


int practice_skill(object me)
{
	return notify_fail("九玄大法只能通过学来提高!\n");
}


string query_type()
{
	return "force_skill";
}

string query_base()
{
	return "force";
}

int query_exercise(object me)
{
	int level;
	level=me->query_skill("jiuxuan-dafa",1);
	if(level<5) return 1;
	return level/5<100?level/5:10;
}

int query_respirate(object me) 
{
	int level;
	level=me->query_skill("jiuxuan-dafa",1);
	if(level<7) return 1;
	return level/7<100?level/7:30;

}

string sub_exercise(object me)
{
	int level;
	level=(int)me->query_skill("jiuxuan-dafa",1);
	if(level<=100) return WHT"$N"+NOR+WHT+"排除一切杂念，盘膝而坐，缓缓运起气来。\n"NOR;
	else if(level<=150) return HIG"$N"+NOR+HIG+"手脚和合扣连环，缓缓运起气来。\n"NOR;
	else if(level<=200) return HIW"$N"+NOR+HIW+"屏息静气，坐了下来，左手搭在右手之上，在胸前"+HIY+"捏了个剑诀，"+NOR+HIW+"引导内息游走各处经脉。\n"NOR;
	else if(level<=250) return YEL"$N"+NOR+YEL+"双手放于膝上，食指伸出，缓缓运起剑气之诀。\n"NOR;
	else if(level<=300) return HIY"$N"+NOR+HIY+"收敛心神，默运九玄大法，将内息缓缓运行了九个周天。\n"NOR;
	else if(level<=350) return HIC"$N"+NOR+HIC+"手捏剑诀，气剑似乎已经溶于一体。\n"NOR;
	else if(level<=400) return HIM"$N"+NOR+HIM+"双手自然地搭在膝上，周身透出阵阵剑气。\n"NOR;
	else return MAG"$N"+NOR+MAG+"手脚和合扣连环，"+HIY+"面色自然，"+NOR+MAG+"已经溶于自然之中。\n"NOR;
}

string sub_respirate(object me)
{
	int level;
	level=(int)me->query_skill("jiuxuan-dafa",1);
	if(level<=100) return WHT"$N"+NOR+WHT+"排除一切杂念，盘膝而坐，缓缓运起气来。\n"NOR;
	else if(level<=150) return HIG"$N"+NOR+HIG+"手脚和合扣连环，缓缓运起气来。\n"NOR;
	else if(level<=200) return HIW"$N"+NOR+HIW+"屏息静气，坐了下来，左手搭在右手之上，在胸前"+HIY+"捏了个剑诀，"+NOR+HIW+"引导内息游走各处经脉。\n"NOR;
	else if(level<=250) return YEL"$N"+NOR+YEL+"双手放于膝上，食指伸出，缓缓运起剑气之诀。\n"NOR;
	else if(level<=300) return HIY"$N"+NOR+HIY+"收敛心神，默运九玄大法，将内息缓缓运行了九个周天。\n"NOR;
	else if(level<=350) return HIC"$N"+NOR+HIC+"手捏剑诀，气剑似乎已经溶于一体。\n"NOR;
	else if(level<=400) return HIM"$N"+NOR+HIM+"双手自然地搭在膝上，周身透出阵阵剑气。\n"NOR;
	else return MAG"$N"+NOR+MAG+"手脚和合扣连环，"+HIY+"面色自然，"+NOR+MAG+"已经溶于自然之中。\n"NOR;
}

string *query_exert() 
{
	return ({"yi","guixi"});
}
