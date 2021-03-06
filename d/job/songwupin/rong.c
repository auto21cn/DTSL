//job.
// 送物品任务。
#include <job_money.h>
#include <ansi.h>
inherit NPC;
string give_job();
mapping target=(["扬州老者":"/d/yangzhou/npc/old","扬州赌徒":"/d/yangzhou/npc/dutu",
"扬州铁匠":"/d/yangzhou/npc/tiejiang","扬州白老夫子":"/d/yangzhou/npc/bai",
"杭州的公子":"/d/hangzhou/npc/gongzi",
"巴陵铁匠":"/d/baling/npc/tiejiang","长安的韦华佗":"/d/changan/npc/weihua-tuo",
"长安的当铺老板铁公鸡":"/d/changan/npc/tie","长安盐局的官差":"/d/changan/npc/guanchai",
"合肥的铁匠":"/d/hefei/npc/tiejiang","九江钱庄的钱老板":"/d/jiujiang/npc/qian",
"襄阳的捕头":"/d/xiangyang/npc/butou","襄阳的铁匠":"/d/xiangyang/npc/tiejiang",
]);
void create()
{
   set_name("荣凤祥",({ "rong fengxiang","rong","fengxiang" }) );
        set("gender", "男性" );
        set("age", 42);
   set("long", "这就是江湖闻明的荣凤祥，他的朋友据说很多。\n");
   set("combat_exp", 600000);
   set("str", 30);
   set_temp("apply/armor",30);
   set_temp("apply/damage",30);
   set_temp("apply/dodge",30);
   set("max_gin",2000);
   set("max_sen",2000);
   set("max_kee",2000);
   set("max_force",2000);
   set("force",2000);
 /*  set("inquiry",([
     "物品":(:give_job:),
     ]));*/
   setup();
   carry_object(__DIR__"cloth")->wear();
  
}

string give_job()
{
  object me,ob;object thing;
  int i;string *jobs,str;
  me=this_player();
  ob=this_object();
  if(me->query_temp("job/rong_job"))
  return "我可不喜欢做事马虎的人！\n";
  if(time()-me->query("busy_time")<90)
  return "我的朋友虽然多，但也不能总是给东西啊！\n";
  if(me->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   if(!valid_do_job(me,"rong"))
	return "你的武功很高了，做这样的小事真是大才小用了！\n";
   me->set_temp("dtsl_job","荣凤祥送物品任务");
  me->set_temp("job/rong_job",1);
  jobs=keys(target);
  i=random(sizeof(jobs));
  thing=new(__DIR__"thing");
  thing->set("owner",target[jobs[i]]);
  thing->move(me);
  str= "麻烦"+RANK_D->query_respect(me)+"你去把"+thing->name()+"\n"+
         "交给(song)"+jobs[i]+"吧，谢谢了！\n";
  if(me->query("combat_exp")>=150000)
  { call_out("killer_come",20+random(5),me);
    str+="路上或许有我的仇家，你要小心！\n";
  }
  return str;
}

void killer_come(object ob)
{
  object killer,letter;
  string kill_msg;
  if(!objectp(ob)){
  remove_call_out("killer_come");return;}
  if(!ob->query_temp("job/rong_job"))
  kill_msg="$N朝$n喝道：你的手脚到挺利索的，拿命来吧！\n";
  else kill_msg="$N朝$n喝道：我和荣凤祥是仇敌，你敢为他办事，拿命来！\n";
  killer=new(__DIR__"killer");
  ob->start_busy(1);
  message_vision(HIB"$N突然觉得一阵冷风吹来！\n"NOR,ob);
  
        killer->set("kee",ob->query("max_kee"));
	killer->set("eff_kee",ob->query("max_kee"));
	killer->set("max_kee",ob->query("max_kee"));
	
	killer->set("gin",ob->query("max_gin"));
	killer->set("eff_gin",ob->query("max_gin"));
	killer->set("max_gin",ob->query("max_gin"));
	
	killer->set("sen",ob->query("max_sen"));
	killer->set("eff_sen",ob->query("max_sen"));
	killer->set("max_sen",ob->query("max_sen"));
	
	killer->set("combat_exp",ob->query("combat_exp"));
	killer->set("max_pot",ob->query("max_pot"));
	if(ob->query("combat_exp")<500000)
	set_all_skill(killer,ob->query("max_pot")-130);
	else
	if(ob->query("combat_exp")<1000000)
	set_all_skill(killer,ob->query("max_pot")-110);
	else
	if(ob->query("combat_exp")<2000000)
	set_all_skill(killer,ob->query("max_pot")-90);
	else
	set_all_skill(killer,ob->query("max_pot")-80);
  killer->set_temp("apply/armor",50+random(50));	 
  killer->move(environment(ob));
  message_vision(kill_msg,killer,ob);
  killer->set_leader(ob);
  killer->kill_ob(ob);
  return;
}