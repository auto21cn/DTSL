
inherit NPC;
#include <ansi.h>
#include <job_money.h>

string *dirs1=({
"/d/gaoli"
});
string *dirs2=({
"/d/changbaishan"
});
string *dirs3=({
"/d/shanhaiguan"
});

string give_job();
int cancel_job();

void create()
{
   set_name("高丽武士",({ "wu shi","wu","shi"}) );
        set("gender", "男性" );
        set("age",42);
        set("long","他是弈剑派的弟子，现在管理高丽的部分治安工作。\n");
  set("max_kee",1000);
  set("max_gin",1000);
  set("max_sen",1000);
  set("max_force",1000);
  set("force",2000);
  set("combat_exp",300000);
  set_skill("unarmed",120);
  set_skill("strike",120);
  set_skill("leg",120);
  set_skill("literate", 120);
 set_skill("force", 120);
  set_skill("dodge", 130);
  set_skill("parry", 150);
  
  set_skill("jiuxuan-dafa",120);
  set_skill("fengxue-leg",130);
  set_skill("xingyun-dodge",130);

  
  set("target_id","####");//防止别人用 ansha 等命令杀他。
  
  set("inquiry",([
     "job":(:give_job:),
     "放弃":(:cancel_job:),
     ]));
  setup();
  
  create_family("弈剑派",5, "弟子");
   carry_object(__DIR__"guanfu")->wear();
  
}

int cancel_job()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("gaoli_kill_job")){
  command("heng "+ob->query("id"));
  return 1;
  }
  
  JOBSYS_D->do_cancel_job("gaolijob",ob,this_object());
  
  return 1;
}

string give_job()
{
  object ob,killer;
  string *dirs;
  
  
  ob=this_player();
  if(ob->query_temp("gaoli_kill_job"))
  return "你还是赶快去找盗贼吧！\n";
   
  if(time()-ob->query("busy_time")<10+random(5))
        return "你还是歇歇吧！\n";
        
  if(ob->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   
   ob->set_temp("dtsl_job","高丽杀盗贼任务");
  
   if(ob->query("combat_exp")<400000)
     dirs=dirs1;
   else
   if(ob->query("combat_exp")<800000)
     dirs=dirs1+dirs2;
   else
     dirs=dirs1+dirs2+dirs3;
   
   killer=new(__DIR__"killer");
   if(!killer->set_status(ob))
    return "天啊！盗贼出了问题，快去报告巫师！\n";
   
   if(!random_place(killer,dirs))
    return "哪里有盗贼呢？让我想想... ...\n";
   
   if(!environment(killer))
    return "哪里有盗贼呢？让我想想... ...\n";
    
  ob->set_temp("gaoli_kill_job",1);
  ob->add_temp_array("job_temp_killer",killer);
  return "据说最近有盗贼在"+MISC_D->find_place(environment(killer))+"活动，你去把他杀了！\n";
}
  
int accept_fight(object who)
{
   return 0;
}

void kill_ob(object ob)
{
  ob->remove_killer(this_object());
  command("bi "+ob->query("id"));
  return;
}
