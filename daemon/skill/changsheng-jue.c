//长生诀

inherit FORCE;

#include <ansi.h>

int valid_learn(object me)
{             
    if((int)me->query_skill("changsheng-jue",1) > 400 )
        return notify_fail("单纯的学习已经无法让你从本质上提高了，自己去领悟精髓吧。 \n");
        return 1;
}


int practice_skill(object me)
{
          return notify_fail("长生诀只能通过领悟来提高!\n");
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

  if(!me->query("force_quest/csj_ok"))
   return 10;
  else
   return 100;
}

int query_respirate(object me) 
{
if(!me->query("force_quest/csj_ok"))
   return 10;
  else
   return 100;
}

string sub_exercise(object me)
{
      if(me->query("force_quest/csj2"))
      return HIB"$N"+HIB+"运气行功，不停地"+BLINK+HIW+"来回走动"+NOR+HIB+"，感觉长生之气遍布全身。\n"NOR;
      else
      return HIW"$N"+HIW+"气沉丹田，随意躺下，运起"+BLINK+MAG+"长生秘诀"+NOR+HIW+",纹丝不动。\n"NOR;
      	
	
}

string sub_respirate(object me)
{
      if(me->query("force_quest/csj2"))
      return HIB"$N"+HIB+"运气行功，不停地"+BLINK+HIW+"来回走动"+NOR+HIB+"，感觉长生之气遍布全身。\n"NOR;
      else
      return HIW"$N"+HIW+"气沉丹田，随意躺下，运起"+BLINK+MAG+"长生秘诀"+NOR+HIW+",纹丝不动。\n"NOR;
}

string *query_exert() 
{
	return ({"wu","luoxuan"});
}

