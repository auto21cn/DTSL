inherit NPC;

#include <job_money.h>
#include <ansi.h>

string give_job();
string abandon_job();

string *dir1=({
"/d/luoyang","/d/yangzhou",
});
string *dir2=({
"/d/xiangyang","/d/jiujiang","/d/baling",
});
string *dir3=({
"/d/gaoli","/d/changan","/d/hefei"
});

void create()
{
   set_name("买卖王",({ "maimai wang","maimai","wang"}) );
   set("gender", "男性" );
   set("age", 40);
   set("long", "这是一个商人，人称[买卖王]，他做生意有一套。\n");
   set("combat_exp",300000);
   set("str",26);
   set("per", 22);
   set("force",500);
   set("max_force",500);
   set("kee",800);
   set("max_kee",800);
   set("sen",500);
   set("max_sen",500);
   set_skill("dodge",80);
   set_skill("parry",80);
   set_skill("force",80);
   set_skill("trade",200);
   set("attitude", "peaceful");
   set("target_id","####");
   set("vocation","商人");
   set("vocation_skill","trade");
   set("inquiry",([
	   "订货":(:give_job:),
           "放弃":(:abandon_job:),
	   ]));
   setup();
   carry_object("/obj/armor/cloth")->wear();
  
}

string give_job()
{
	object me,order;
        object owner;
        string *dirs,str;
	me=this_player();
        
        if(me->query("vocation")!="商人")
	        return "我只相信商人。\n";
        if(me->query_skill("trade",1)>me->query("int")*8)
                return "你现在是独当一面的商人了，再做这些任务太委屈你了。\n";
	if(me->query_temp("order_job"))
		return "你还是把手中的订货单送出去吧。\n";
	if(time()-me->query("busy_time")<=50)
		return "现在不景气，你还是歇歇吧！\n";
	if(me->query_temp("dtsl_job"))
                return "你正在做其他任务，先忙其他的吧！\n";
        if(me->query("combat_exp")<500000)
	 dirs=dir1;
	else
	 if(me->query("combat_exp")<1000000)
	 dirs=dir1+dir2;
	else
	 dirs=dir1+dir2+dir3;
       
        owner=new(__DIR__"owner");
        
        owner->set_status(me);
  
        if(!random_place(owner,dirs))
        return "收货人在哪里呢？让我想想... ... ... ...\n";
        
        if(!environment(owner))
        return "收货人在哪里呢？让我想想... ...\n"; 
       
        order=new(__DIR__"order");
	order->set("target",owner);
	order->set("long","这是一张送给"+HIC+owner->name()+NOR+"的订货单。\n");
	order->set("owner",me);
	order->move(me);
	me->set_temp("dtsl_job","乐寿买卖王订货任务");
	
	me->set_temp("order_job",1);

         if(me->query("combat_exp",1)>=1000000)
	  me->set_temp("need_killer",2);
        else
         if(me->query("combat_exp",1)>=500000)
	  me->set_temp("need_killer",1);
	else
	  me->set_temp("need_killer",0);
	 if((int)me->query("combat_exp",1)>=500000)
	   {   
	   	call_out("killer_come",20+random(10),me);
            str="速去速回，不要贻误商机！\n";
	}
        else str="";
	tell_object(me,query("name")+"给了一张"+order->query("name")+"。\n");
	return "好吧，麻烦你帮我把这张"+order->query("name")+CYN+"送给在"+MISC_D->find_place(environment(owner))+
	 "的"+owner->name()+"，十万火急，快去快去！\n"+
	       str;
	
	 
}

string abandon_job()
{
   object ob;
   object order;
   
   ob=this_player();
   
   if(!ob->query_temp("order_job")){
   command("heng "+ob->query("id"));
   return "快走开，我还忙着呢！\n";
   }
   
   JOBSYS_D->do_cancel_job("tradejob",ob,this_object());
   
   return "象你这种人怎么能当商人。\n";
}

void killer_come(object me)
{
  object killer;
   object killer2;
   object order;
   
   if(!me)
    return;
   if(me->is_ghost())
    return;
   
   if(!me->query_temp("order_job"))
    return;
    
   tell_object(me,HIB"\n似乎有人从你的背后袭来！\n\n"NOR);
   	killer=new("/d/job/trade/killer");
   	
   	killer->set_status(me);	
	
	killer->move(environment(me));
	message_vision("\n$N大声道:你等着破产吧!\n",killer);
	me->add_temp_array("job_temp_killer",killer);
	killer->kill_ob(me);
	
        if(me->query("combat_exp")>=500000){
          killer2=new("/d/job/trade/killer");
          killer2->set_status(me);	
          killer2->move(environment(me));
          me->add_temp_array("job_temp_killer",killer2);
          killer2->kill_ob(me);}
     return;
}	

int is_apprentice_of(object ob)
{
        return 1;
}

int recognize_apprentice(object ob)
{
   return 1;
}

int prevent_learn(object me,string skill)
{
   if(me->query("vocation")!=query("vocation")){
     command("say 你又不是"+query("vocation")+"，我可不传授你技能！");
     return 1;
   }
   if(skill!=query("vocation_skill")){
    command("say 我只传授"+to_chinese(query("vocation_skill"))+
             "「"+query("vocation_skill")+"」！");
    return 1;
   }
   return 0;
}
    

