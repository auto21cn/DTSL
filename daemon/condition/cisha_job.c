
#include <ansi.h>
#include <condition.h>
#include <job_money.h>

inherit F_CLEAN_UP;

int update_condition(object me, int times)
{
   
   object *t;
   object killer;
   object swap;
   int i;
   
   if(!me->query_temp("dtsl_job_cisha"))
    return 0;
   if(times>0)
   tell_room(environment(me),YEL"只听远处有人谈笑的声音，似乎就是任少名来了。\n"NOR);
   
   if(times<=0){
   	
   	t=me->query_team();
   	if(sizeof(t)>0){
   	 swap=t[0];
   	 for(i=1;i<sizeof(t);i++)
   	  if(t[i]&&environment(t[i])==environment(me))
   	    if(t[i]->query("combat_exp")>swap->query("combat_exp"))
   	      swap=t[i];}
   	else swap=me;
   	killer=new("/d/job/cisha/killer");
        set_all_skill(killer,swap->query("max_pot")-80);
        killer->set("combat_exp",swap->query("combat_exp"));
 if("/cmds/usr/hp.c"->get_pot(killer));
   	killer->move("/d/job/cisha/chunyuan");
   	tell_room(environment(me),YEL"只听楼下的声音更加真切，确实是任少名来了！\n"NOR);
   	if(sizeof(t)>0){
   	 message_vision(HIG"只听$N一声清啸：任少名狗贼已经到了楼下，各位上啊！！\n"NOR,me);
   	 tell_room("/d/job/cisha/chunyuan","只听楼上有人喊了一声，接着跳下了数个人！\n");
   	 for(i=0;i<sizeof(t);i++)
   	  if(t[i]&&living(t[i])){
   	    message_vision("只听蹭地一声，$N破窗而出！！\n",t[i]);
   	    killer->add_array("target_id",t[i]->query("id"));
   	    t[i]->move("/d/job/cisha/chunyuan");}
   	 message_vision(HIW"$N朝$n怒目而视：原来是你个小贼！尽管让你的同伙一起上吧！\n"NOR,killer,me);
   	 killer->kill_ob(me);
   	 return 0;}
   	else{
   	message_vision(HIG"只听$N一声清啸：任少名狗贼休要逃跑！\n"NOR,me);
   	 tell_room("/d/job/cisha/chunyuan","只听楼上有人喊了一声，接着跳下来一个人！\n");
   	message_vision(HIW"$N朝$n怒目而视：原来是你个小贼！尽管来吧！\n"NOR,killer,me);
   	killer->set("target_id",me->query("id"));
   	me->move("/d/job/cisha/chunyuan");
   	killer->kill_ob(me);
   	return 0;}
   	}
   	   
      me->apply_condition("cisha_job", times - 1);
   if( times < 1 ) return 0;
   return CND_CONTINUE;
}
