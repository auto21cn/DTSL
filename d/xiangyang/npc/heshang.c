
inherit NPC;
#include <ansi.h>
mapping *ask=({
([
 "ask":HIW"菩提本非树,明镜亦非台"NOR,
 "answer":"本来无一物,何处惹尘埃",
 ]),
 ([
 "ask":HIW"何名坐禅？"NOR,
 "answer":"内见自性不动，名为禅",
 ]),
 ([
 "ask":HIW"何名禅定？"NOR,
 "answer":"外禅内定，是为禅定",
 ])
});

int do_answer(string arg);
void create()
{
       set_name("和尚", ({ "he shang","he","shang"}) );
       set("gender", "男性" );
       set("age", 30);
       set("long","这是白马寺的僧人.\n");
       set("combat_exp", 12500);
       set("attitude", "friendly");
       set("class","bonze");
       setup();
 carry_object(__DIR__"obj/sengyi")->wear();


}
void init()
{
	object *ob,here;int i;
	add_action("do_answer","answer");
    here=find_object("/d/yangzhou/baimasi");
	ob=all_inventory(here);
  for(i=0;i<sizeof(ob);i++)
	{
		if(ob[i]->query_temp("buzhi_jiangjing/2")
			&&!ob[i]->query_temp("buzhi_jiangjing/flag"))
			call_out("ask_quest",1,ob[i]);
	}
	return;
        
}

void ask_quest(object me)
{
	object ob;mapping ask_msg;
	ob=this_object();
	me->set_temp("buzhi_jiangjing/flag",1);
    ask_msg=ask[random(sizeof(ask))];
	ob->set("ask",ask_msg);
 	message_vision("$N向$n问道:"+ask_msg["ask"]+",此句做何解释?\n",ob,me);
    call_out("clear_jiangjing",60,ob,me);



   remove_call_out("ask_quest");
   return;
}

void clear_jiangjing(object ob,object me)
{
	if(me->query_temp("buzhi_jiangjing"))
	{ob->delete("ask");
	me->delete_temp("buzhi_jiangjing");
	message_vision("$N冲着$n叹道:你还是回去好好学学在来吧!\n",ob,me);
	remove_call_out("clear_jiangjing");}
	else remove_call_out("clear_jiangjing");
	return;
}

int do_answer(string arg)
{
	object me,ob,bonze,ans;
	int lev,exp,pot;
	mapping answer;
	me=this_player();
	if(!arg) return notify_fail("你想回答什么?\n");
	if(sscanf(arg,"%s %s",bonze,ans)!=2)
		return notify_fail("请使用 answer 人名 答案\n");
	if(!objectp(ob=present(bonze,environment(me))))
		return notify_fail("这里没有这个人!\n");
	if(!ob->query("ask"))
		return notify_fail(ob->name()+"并没有问你问题!\n");
	answer=ob->query("ask");
	if(ans!=answer["answer"])
		return notify_fail("你的答案不对!\n");
	me->delete_temp("buzhi_jiangjing");
	ob->delete("ask");
	exp=(int)me->query("combat_exp",1);
	if(exp<=999) exp=50+random(5);
	else if(exp<=9999) exp=exp/100+50+random(5);
	else if(exp<=99999) exp=exp/1000+200+random(5);
	else exp=exp/10000+500+random(5);
	pot=(int)me->query("max_pot");
	pot=pot/3;
	lev=20+random(5);
	me->add("combat_exp",exp);
	me->add("potential",pot);
	me->improve_skill("chanzong-fofa",lev);
	tell_object(me,"在这次讲经过程中,你得到了"+""HIW""+chinese_number(exp)+""NOR""+"点经验值 "+""HIW""+chinese_number(pot)+""NOR""+"点潜能 \n");
	tell_object(me,"你的"+""HIW""+"[禅宗佛法]"+""NOR""+"的修为也有了进一步的提高!\n");
	message_vision("$N合十道:大师高明,谢谢!\n",ob);
	return 1;
}
	