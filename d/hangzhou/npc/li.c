#include <ansi.h>
#include <job_money.h>
inherit NPC;
string give_job();
int do_ok(string arg);
void create()
{
   set_name("李财主",({ "li caizhu","li","caizhu" }) );
        set("gender", "男性" );
        set("age", 52);
   set("long", "这是杭州的大富李财主，近来他正在为女儿举办比武招亲。\n");
       
   set("combat_exp", 50000);
   set("str", 10);
   set("per", 22);
   set("attitude", "friendly");
   set("inquiry",([
	   "比武招亲":(:give_job:),
	   ]));
   set("chat_chance",80);
   set("chat_msg",({
	   (:random_move:),
   }));
   setup();
   carry_object(__DIR__"obj/chouyi")->wear();
  
}

void init()
{
	add_action("do_ok","task");
}

string give_job()
{
	object me,ob,letter;
	me=this_player();ob=this_object();
	if(me->query_temp("li_job"))
		return "你还是先做完手头的事吧！\n";
	if(ob->query_temp("defence_girl"))
		return "谢谢这位"+RANK_D->query_respect(me)+"了，应经有人帮忙保护我女儿了！\n";
	if(time()-me->query("busy_time")<=150+random(10))
		return "你还是先歇歇吧！\n";
	if(me->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   me->set_temp("dtsl_job","杭州李财主任务");
	me->set_temp("li_job",1);
	me->set("busy_time",time());
	switch(random(3))
	{  case 0:
	me->set_temp("defence_girl",1);
	ob->set_temp("defence_girl",1);
	call_out("cancel_job",180,me,ob);
	return "什么比武招亲啊！杨广这个奸贼看上了我的女儿，就要派人来抢了！\n麻烦"+RANK_D->query_respect(me)+"保护我的女儿吧！\n";
	break;
	   case 1:
		me->set_temp("li_songxin_job/1",1);
		me->start_busy(2);
		letter=new(__DIR__"obj/letter");
		letter->move(me);
		return "好吧，麻烦"+RANK_D->query_respect(me)+"把这封请柬送到洛阳钱庄的孙老板那里吧！\n";
		break;
	   case 2:
		me->set_temp("li_songxin_job/2",1);
		me->start_busy(2);
		letter=new(__DIR__"obj/letter");
		letter->move(me);
		return "好吧，麻烦"+RANK_D->query_respect(me)+"把这封请柬送到成都[川南赌坊]的掌柜霍青桥那里吧！\n";
		break;
	}
}

void cancel_job(object me,object ob)
{
	if(!objectp(me)||!objectp(ob))
	{ remove_call_out("cancel_job");return;}
	if(me->query_temp("defence_girl"))
		if(!me->query_temp("defence_ok"))
		{ tell_object(me,"李财主朝你喊道：象你这么没用，我女儿早就没了！我不用你了！\n");
		  me->delete_temp("defence_girl");
		  me->delete_temp("defence_flag");
		  ob->delete_temp("defence_girl");
          remove_call_out("cancel_job");return;
		}
	remove_call_out("cancel_job");return;
}

int do_ok(string arg)
{
	object me,ob,money;
	int exp,i,sil,pot,famous,score;
	me=this_player();i=0;
	ob=this_object();
	if(!me->query_temp("defence_girl"))
		return notify_fail("什么？\n");
	if(!arg||arg!="ok")
		return notify_fail("如果复命，请用task ok.\n");
	if(!me->query_temp("defence_ok"))
		return notify_fail("你不杀死官兵，怎么救我女儿啊！\n");
	exp=me->query("max_pot")+random(5);
	sil=LI_DEFENCE_JOB+me->query("max_pot")/5;
	pot=me->query("max_pot")/3;
	if(me->query("vocation")=="杀手")
	{  me->add("vocation_score",exp/3);
	   me->add("vocation_exp",exp/4);
	}
	me->add("combat_exp",exp);
	me->add("potential",pot);
	me->add("deposit",sil);
	add_shili(me,exp/2,LI_DEFENCE_JOB/2);
	me->delete_temp("defence_girl");
	me->delete_temp("defence_flag");
	me->delete_temp("defence_ok");
	me->delete_temp("li_job");
	me->delete_temp("dtsl_job");
    ob->delete_temp("defence_girl");
	tell_object(me,"在这次行动中，你增长了"+""HIW""+chinese_number(exp)+""NOR""+"点战斗经验，"
                                          +""HIW""+chinese_number(pot)+""NOR""+"点潜能.\n");
	if(me->query("vocation")=="杀手")
	tell_object(me,"由于你是杀手，你的职业声望和职业经验都提高了！\n");
	tell_object(me,"李财主奖励了你"+MONEY_D->money_str(sil)+"\n");
	tell_object(me,"你钱庄的存款增加了！\n");
	return 1;
}
