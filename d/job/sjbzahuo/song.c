
inherit NPC;

#include <ansi.h>
#include <job_money.h>


mapping here=([
"兵器室":"/d/lingnan/bingqishi",
"休息室":"/d/lingnan/xiuxishi",
"磨刀堂":"/d/lingnan/modaotang",
"货物房":"/d/lingnan/huowufang",
]);

string give_job();
int do_ok(string arg);
int cancel_job();

void create()
{
   set_name("宋婆婆",({ "song popo","song","popo" }) );
        set("gender", "女性" );
		
        set("age", 70);
   set("long", "这是在宋家堡做杂活的宋婆婆，年事已高了。\n");
       
   set("combat_exp", 50000);
   set("str", 25);
   set("attitude", "peaceful");
   set_skill("blade",30);
   set_skill("tiandao-bajue",30);
   set_skill("dodge",30);
   set_skill("force",30);
   set("force",200);
   set("target_id","###");
   set("inquiry",([
      "job":(:give_job:),
      "放弃":(:cancel_job:),
      ]));
   setup();
  
}

void init()
{
   add_action("do_ok","task");
}

string give_job()
{
  object ob,tool;
  string *where;
  int i;
  
  ob=this_player();
  
   if(ob->query("family/family_name")!="宋家堡")
   return "只有宋家堡的弟子才可以做这个任务。\n";
   
   if(ob->query("combat_exp")>=100000)
   return "凭你的身手做这样的事情真是可惜了！\n";
   
   if(ob->query_temp("sjb_saochu"))
   return "你做事可要有头有尾，不要马马乎乎。\n";
   
   if(time()-ob->query("busy_time")<10+random(10))
   return "年轻人做事何必急于一时呢，还是先歇会吧！\n";
   
   if(ob->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   
   ob->set_temp("dtsl_job","宋家堡打杂任务");
   ob->set_temp("sjb_saochu",1);
   
   where=keys(here);
   i=random(sizeof(where));
   
   tool=new(__DIR__"tool");
   tool->set("owner",ob);
   tool->set("place",here[where[i]]);
   
   tool->move(ob);
   ob->add_temp_array("job_temp_killer",tool);
   tell_object(ob,query("name")+"给了你一把"+tool->name()+"。\n");
   return "好吧，麻烦你去"+where[i]+"打扫一下卫生吧！\n";
}

int do_ok(string arg)
{
   object ob,target;
   string paper_name;
   
   ob=this_player();
   
   if(!arg||sscanf(arg,"ok with %s",paper_name)!=1)
   return notify_fail("你得使用 task ok with xx 来交差。\n");
   if(!ob->query_temp("sjb_saochu"))
  return notify_fail("你没有向"+query("name")+"要这个任务。\n");
   if(!objectp(target=present(paper_name,ob)))
   return notify_fail("你身上没有这个东西！\n");
   if(target->query("owner")!=ob)
  return notify_fail("这不是你的扫帚！\n");
   if(!target->query("ok"))
   return notify_fail("你还没干完活，继续去扫除吧！\n");
   
  tell_object(ob,query("name")+"拍拍你的头：好，干得不错！\n");
  target->unequip();
  destruct(target);
   
   JOBSYS_D->give_reward_sjbzahuo(ob);
   
   ob->delete_temp("sjb_saochu");
   ob->delete_temp("sjb_saochu_times");
   ob->delete_temp("dtsl_job");
   ob->set("busy_time",time());
   return 1;
}

int cancel_job()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("sjb_saochu")){
  
  command("?");
  return 1;
  }
  JOBSYS_D->do_cancel_job("sjbzahuo",ob,this_object());
  
  command("say 这点小事你都做不好，以后怎么闯荡江湖啊！\n");
  return 1;
}
