
#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
   string force,*force_skill,*force_exert,exert;
   int result,i,flag;string tar,ski;
   int p_damage;
   
   seteuid(getuid());
   flag=0;
   if( me->is_busy() )
     return notify_fail("( 你上一个动作还没有完成，不能施用内功。)\n");
   if(me&&environment(me)&&environment(me)->query("no_exert"))
   return notify_fail("这里不能使用内功!\n");
   if(!arg) return notify_fail("你要用内功做什么？\n");
   if(sscanf(arg,"%s %s",ski,tar)==2||sscanf(arg,"%s on %s",ski,tar)==2)
       arg=ski+" "+tar;
   else ski=arg;
   force_skill=me->query("force_skill");
   if(sizeof(force_skill)==0&&!me->query_skill("force"))
	   return notify_fail("你没有学会任何内功!\n");
   
   p_damage=me->query_temp("bsy_skill_damage");
   if(p_damage&&time()-me->query_temp("bsy_damage_time")<p_damage/7){
        tell_object(me,"\n你受了不死印的伤，内伤加剧了！\n");
        me->receive_wound("kee",p_damage*3/2);
        return 1;
   }
   
   for(i=0;i<sizeof(force_skill);i++)
   {
	   force_exert=SKILL_D(force_skill[i])->query_exert();
	   if(sizeof(force_exert)<=0) continue;
	   if(sizeof(force_exert-({ski}))<sizeof(force_exert))
	   {
		   flag=1;break;
	   }
	  
   }
   if(flag==1) 
   {
     
     if( SKILL_D("force")->exert_function(me, arg) ) 
	 {

       
        return 1;
     }
	 else return (int)SKILL_D("force")->exert_function(me,arg);
   }
   else 
   {
	   force_exert=SKILL_D("force")->query_exert();
       if(sizeof(force_exert-({ski}))<sizeof(force_exert))
	   {
		   if( SKILL_D("force")->exert_function(me, arg) ) 
			   return 1;
		   else return (int)SKILL_D("force")->exert_function(me,arg);
	   }

	   else return notify_fail("你的内功没有这种功能!\n");
   }
 


}

