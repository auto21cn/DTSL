//execute.c

inherit F_CLEAN_UP;
#include <skill.h>

int main(object me, string arg)
{
	object target;
	string type,*executes,*skl,exec;
	mapping skills;
	int i;int flag;
	
	flag=0;
	seteuid(getuid());

	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成，不能施用心法。\n");
                        
    if( !arg ) return notify_fail("你要使用什么心法？\n");
   if ( !wizardp(me)&&environment(me) && environment(me)->query("no_fight")&&!environment(me)->query("leitai")) 
     return notify_fail("这里不能使用心法。\n");

   if( sscanf(arg, "%s on %s", exec, arg)==2 ) {
   	target = present(arg, environment(me));
    if( !target ) target = present(arg, me);
    if( !target ) return notify_fail("这里没有 " + arg + "。\n");

    if( userp(me) && userp(target) && 
       	target->query_temp("netdead") )
    	return notify_fail("对方正在断线中，不能对其施用心法。\n");
    	arg=exec+" "+arg;
   } 
   else 
   if(sscanf(arg, "%s %s", exec, arg)==2 ) {
     arg=exec+" "+arg;
   } 
   else 
   	exec=arg;
		
   skills=me->query_skills();
   if(!sizeof(skills)) 
		return notify_fail("你没有任何技能!\n");
	 skl=keys(skills);
	
	for(i=0;i<sizeof(skl);i++)
	{
     executes=SKILL_D(skl[i])->query_execute();
	   if(!sizeof(executes)) continue;
	   if(member_array(exec,executes)!=-1)
	   {
		   flag=1;
		   type="xinfa";
		   break;
	   }
	} 
       if(flag==0)
       return notify_fail("你没有这个心法可以施展!\n");
          
       return (int)SKILL_D(type)->execute_action(me,arg);
}

int help()
{
  write("
    可以使用这个命令来使用你所学的心法。
\n");
return 1;
}