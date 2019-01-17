//禅宗佛法。静念禅院
inherit SKILL;

int valid_learn(object me)
{
    if((int)me->query_skill("chanzong-fofa",1) > 400 )
        return notify_fail("单纯的学习已经无法让你从本质上提高了，自己去领悟精髓吧。 \n");
	if((int)me->query("PKS",1)>=5)
	return notify_fail("你感到自己所犯的杀戒太重，不能继续学习下去了！\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("禅宗佛法只能通过学来提高!\n");
}

string query_type()
{
	return "literate";
}

string help_action()
{
write(@LONG
    禅宗佛法

    净念禅院的佛法。      
LONG);
return "\n";
}
