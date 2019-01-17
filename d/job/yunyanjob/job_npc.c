
inherit NPC;

#include <job_money.h>
#include <ansi.h>

#define JOBCTRL __DIR__"jobctrl.c"


string give_job()
{
   object ob,obj,jobctrl;
   int i;
   mapping line;
   
   ob=this_player();
   jobctrl=load_object(JOBCTRL);
   jobctrl->start_job();
   i=jobctrl->give_job(environment(ob)->query("job_name"));
   if(!i)
   return "现在这里没有盐车需要押送，你还是去其他城市看看吧！\n";
   
   if(ob->query_temp("yunyan_job"))
   return "你赶快去运盐吧！\n";
   
   if(time()-ob->query("busy_time")<40+random(10))
   return "你歇会再继续干活吧！\n";
   
   if(ob->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   
   jobctrl->reset_job(i);
   
   obj=new(__DIR__"yanche");
   line=jobctrl->get_this_line(i);
   obj->set("line",line);
   obj->set("owner",ob);
   obj->set("last_time",time());
   obj->move(environment(ob));
   ob->set_temp("track",obj);
   obj->set("long","这是由"+ob->name()+"负责押送的从"+line["from"]+"到"+
    line["to"]+"的"+obj->query("name")+"。\n");
   ob->add_temp_array("job_temp_killer",obj);
   ob->set_temp("yunyan_job",1);
   ob->set_temp("dtsl_job","运盐任务");
   
   if(ob->query("combat_exp")>=200000){
   
   if(ob->query("combat_exp")<500000)
    ob->set_temp("need_killer",1);
   else
    ob->set_temp("need_killer",2);
   
   call_out("killer_come",30+random(5),ob);
   }
   
   return "好吧，那你就把这个"+obj->query("name")+"运送到"+
   line["to"]+"吧！\n";
}
   
   

int do_ok(string arg)
{
	object track,me,ob;
	object *killers;
	int i;
	
	me=this_player();
	ob=this_object();
	
	if(!arg||arg!="ok") return notify_fail("请使用task ok来复命!\n");
	if(!me->query_temp("yunyan_job"))
		return notify_fail("你没有向官府领任务，难道想来冒领吗?\n");
	if(!objectp(track=present("yan che",environment(me))))
		return notify_fail("你把盐车弄丢了，还复什么命啊？\n");
	if(track->query("owner")!=me)
		return notify_fail("这不是你的盐车!\n");
	if(track->query("line/to")!=environment(ob)->query("job_name"))
	return notify_fail("你的盐车送错地方了！\n");
	message_vision("$N朝里面喊道：把盐车拉进去！\n马上出来一个官兵，把盐车拉进去了!\n",ob);
	JOBSYS_D->give_reward_yunyanjob(me,track->query("line/dif"));
	if(objectp(track))
	destruct(track);		
	me->delete_temp("yunyan_killer");
	me->delete_temp("yunyan_job");
	me->delete_temp("dtsl_job");			
	me->delete_temp("need_killer");
	me->delete_temp("need_killer_flags");
	me->set("busy_time",time());
	
	return 1;
}

string give_line()
{
	object me,jobctrl;
	string str;
	
	me=this_player();
	str="";
	
	jobctrl=load_object(JOBCTRL);
	jobctrl->start_job();
	str=jobctrl->get_line();
	
	me->start_more(str);
	
	return "路途远近不同，官府给你的奖励自然不同。你仔细选择吧！\n";
}
string abandon_job()
{
  object me;
  object track;
  me=this_player();
  if(!me->query_temp("yunyan_job"))
  return "你说什么呢？戏弄本官吗？\n";
  
  JOBSYS_D->do_cancel("yunyan",me,this_object());
  
  	me->delete_temp("yunyan_killer");
	me->delete_temp("yunyan_job");
	me->delete_temp("dtsl_job");			
	me->delete_temp("need_killer");
	me->delete_temp("need_killer_flags");
  
  if(objectp(track=me->query_temp("track"))){
   track->delete("last_time");
   destruct(track);}
  
  return "唉，如今肯为官府办事的人是越来越少了！\n";
}


void killer_come(object me)
{
   object killer;
   object killer2;
   
   if(!me) return;
   if(!me->query_temp("yunyan_job"))
    return;
   if(!objectp(me->query_temp("track")))
    return;
    
    tell_object(me,HIB"\n突然一阵冷风吹了过来！\n\n"NOR);
   	killer=new("/d/job/yunyanjob/killer");   	
   	
   	killer->set_status(me);
   	me->add_temp_array("job_temp_killer",killer);
   	killer->move(environment(me));
   	
   	message_vision("\n$N朝$n喊道：此山是我开，此树是我栽！留下你的盐车吧！！\n\n",
   				killer,me);
   	killer->kill_ob(me);
   	   	
    if(me->query("combat_exp")>=500000){
        killer2=new("/d/job/yunyanjob/killer");
        
        killer2->set_status(me);
        me->add_temp_array("job_temp_killer",killer2);
        killer2->move(environment(me));
        
        message_vision("\n$N喊道：点子武功高强，兄弟们并肩子上啊！！\n\n",
   				killer);
   			killer2->kill_ob(me);
        
    }
              
      return;
}	           