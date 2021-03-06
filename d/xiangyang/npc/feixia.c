
inherit NPC;
#include <ansi.h>

mapping *quest=({
	([
          "ask":HIW"请问 (100+100)/2 等于多少?\n"NOR,
		  "ans":"100",
	]),
	([
	      "ask":HIW"请问隋朝之后是什么朝代?\n"NOR,
		  "ans":"唐朝",
	]),
});

mapping *name_id=({
	([
		"name":"王",
		"id":"wang",
	]),
	([
		"name":"赵",
		"id":"zhao",
	]),
	([
		"name":"刘",
		"id":"liu",
	]),
	([
		"name":"欧阳",
		"id":"ouyang",
	]),
});
string *name=({"无敌","剑","无悔","霸","青天"});
int do_answer(string arg);
void create()
{   
    mapping nameid;
	nameid=name_id[random(sizeof(name_id))];
	set_name(nameid["name"]+name[random(sizeof(name))],({ nameid["id"]}) );
        set("gender", "男性" );
        set("age", 12);
		
   set("long", "他是游荡于世界飞侠,专门负责检查近来的[机器人]事件。\n");
       
   set("combat_exp", 5000);
   set("str", 20);
   set("per", 25);
   set_skill("unarmed",20);
   set_skill("dodge",20);
   set_skill("parry",20);
   
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
 
}

int accept_fight(object ob)
{
	return notify_fail(ob->name()+"笑道:君子动口不动手啊!\n");
}

void die()
{  object ob;
   ob=this_player();
   message_vision("$N笑道:我是不死战士!\n",ob);
   return;
}

void init()
{
	object *ob;object me,here;int i;
	add_action("do_answer","answer");
	me=this_object();

    here=environment(me);
	ob=all_inventory(here);
	for(i=0;i<sizeof(ob);i++)
	{  if(userp(ob[i]))
		if(!me->query("followed"))
		{
			
				me->set("followed",1);
				me->set_leader(ob[i]);
				message_vision(HIW"$N决定调查$n一段时间!\n"NOR,me,ob[i]);
				call_out("ask_quest",30+random(2),me,ob[i]);
				break;
			
		}
	}
	return;
}

void ask_quest(object me,object ob)
{
	mapping que;
	if(!objectp(ob)) {remove_call_out("ask_quest");return;}
	que=quest[random(sizeof(quest))];
	me->set("ans",que["ans"]);
	ob->set_temp("check",1);
	tell_object(ob,que["ask"]);
	remove_call_out("ask_quest");
	call_out("wait",15,me,ob,30);
	return;
}

void wait(object me,object ob,int i)
{
	if(!objectp(ob)) {remove_call_out("wait");return;}
	if(ob->query_temp("check"))
	{
		if(i==30) message_vision(HIW"$N捅了捅$n,发什么呆啊?\n"NOR,me,ob);
		else if(i==20) message_vision(HIW"$N拍了拍$n的头:不会吧,这么简单的问题都不会?\n"NOR,me,ob);
		else if(i==10) message_vision(HIW"$N朝$n冷笑道:我看你十有八九是机器人了!\n"NOR,me,ob);
		else {
			   message_vision(HIW"$N朝$n叫道:好你个机器人,敢和我弄虚做假!\n"NOR,me,ob);
	           call_out("goto_rock",1,me,ob);
		}
		i=i-10;
		call_out("wait",10,me,ob,i);
		return;
	}

    remove_call_out("wait");return;
}

void goto_rock(object me,object ob)
{
	if(!objectp(ob)) {remove_call_out("goto_rock");return;}
	me->set_leader(0);
	me->delete("followed");
	ob->delete_temp("check");
	me->delete("ans");
	message_vision("$N冲着$n叹道:你还是去[思过崖]去悔改吧!\n",me,ob);
	ob->move(__DIR__"siguoya");
    remove_call_out("goto_rock");return;
}

int do_answer(string arg)
{
	object me;string target,ans,answer;object ob;
	me=this_player();
	if(!arg) return notify_fail("请使用answer 人名 问题\n");
	if(sscanf(arg,"%s %s",target,ans)!=2)
		return notify_fail("请使用answer 人名 问题\n");
	if(!objectp(ob=present(target,environment(me))))
		return notify_fail("这里没有这个人!\n");
	if(!me->query_temp("check"))
		return notify_fail("小飞侠没有问你问题!\n");
	answer=ob->query("ans");
	if(answer!=ans)
		return notify_fail("小飞侠敲瞧你的头:仔细点,好好想想!\n");
	me->delete_temp("check");
	ob->delete("ans");
	ob->delete("followed");
	ob->set_leader(0);
	message_vision(HIW"$N笑道:好,真是打扰$n了!\n"NOR,ob,me);
	return 1;
}