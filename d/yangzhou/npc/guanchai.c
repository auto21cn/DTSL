#include <job_money.h>
inherit NPC;
string give_job();
string abandon_job();
void create()
{
        set_name("官差", ({"guan chai", "guan","chai"}));
        set("title", "盐局官差");
        set("gender", "男性");
        set("age", 34);

        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);

        set("kee", 500); 
        set("max_kee", 500);
        set("gin", 100);
        set("max_gin", 100);
        set("sen",300);
        set("max_sen",300);
        set("combat_exp",300000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("env/wimpy", 50);

        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 200);
		set_skill("cuff",120);
		set_skill("force",120);
		set_skill("wuxing-quan",130);
        set("hand",({"wuxing-quan"}));
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);
        set("inquiry",([
			"运盐":(:give_job:),
			"放弃":(:abandon_job:),
			]));

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}

string give_job()
{
	object me,ob;object obj;string str;
	me=this_player();
	ob=this_object();
	str="";
	if(me->query_temp("guanchai_yunyan"))
		return "这位"+RANK_D->query_respect(me)+",为官府做事可不能这么不认真!\n";
	if(time()-me->query("busy_time")<=180)
		return "这位"+RANK_D->query_respect(me)+",你还是先歇歇吧!\n";
	if(me->query_temp("dtsl_job"))
        return "你正在做其他任务，先忙其他的吧！\n";
        if(!valid_do_job(me,"yunyan"))
	return "你的武功很高了，做这样的小事真是大才小用了！\n";
	obj=new(__DIR__"obj/yanche");
        me->set_temp("dtsl_job","扬州关差运盐任务");
	obj->move(environment(me));
	me->set_temp("track",obj);
	me->set("busy_time",time());
	obj->set("owner",me);
	obj->set("last_time",time());
	if(me->query("combat_exp")>=200000)
	call_out("dao_come",15+random(2),me,obj);
	switch(random(5))
	{
	case 0:me->set_temp("guanchai_yunyan/1",1);
		   str=str+ "好吧，麻烦"+RANK_D->query_respect(me)+"把这车盐送到洛阳的盐局吧!\n";
		   obj->set("long","这是一辆由"+me->name()+"护送送往洛阳盐局的盐车。\n");
		   break;
	case 1:me->set_temp("guanchai_yunyan/2",1);
		   str=str+ "好吧，麻烦"+RANK_D->query_respect(me)+"把这车盐送到成都的盐局吧!\n";
		   obj->set("long","这是一辆由"+me->name()+"护送送往成都盐局的盐车。\n");
		   break;
	case 2:me->set_temp("guanchai_yunyan/3",1);
		   str=str+ "好吧，麻烦"+RANK_D->query_respect(me)+"把这车盐送到襄阳的盐局吧!\n";
		   obj->set("long","这是一辆由"+me->name()+"护送送往襄阳盐局的盐车。\n");
		   break;
	case 3:me->set_temp("guanchai_yunyan/4",1);
		   str=str+ "好吧，麻烦"+RANK_D->query_respect(me)+"把这车盐送到九江的盐局吧!\n";
		   obj->set("long","这是一辆由"+me->name()+"护送送往九江盐局的盐车。\n");
		   break;
	case 4:me->set_temp("guanchai_yunyan/5",1);
		   str=str+ "好吧，麻烦"+RANK_D->query_respect(me)+"把这车盐送到长安的盐局吧!\n";
		   obj->set("long","这是一辆由"+me->name()+"护送送往长安盐局的盐车。\n");
		   break;
	}
	if(me->query("combat_exp")>=200000)
	str=str+"路上小心强盗!\n";
	return str;
}
string abandon_job()
{
  object me;
  object track;
  me=this_player();
  if(!me->query_temp("guanchai_yunyan"))
  return "你说什么呢？戏弄本官吗？\n";
  me->delete_temp("guanchai_yunyan");
  me->delete_temp("dtsl_job");
  if(objectp(track=me->query_temp("track"))){
   track->delete("last_time");
   destruct(track);}
  me->delete_temp("track");
  me->set("busy_time",time()+20);
  return "唉，如今肯为官府办事的人是越来越少了！\n";
}
void dao_come(object me,object obj)
{
        object killer,killer2;
	if(!me||!obj||!me->query_temp("guanchai_yunyan"))
        { return;}
	killer=new(__DIR__"killer");
if(me->query("combat_exp")>500000)
        killer2=new(__DIR__"killer");
	
	killer->set("kee",me->query("max_kee"));
	killer->set("eff_kee",me->query("max_kee"));
	killer->set("max_kee",me->query("max_kee"));
	
	killer->set("gin",me->query("max_gin"));
	killer->set("eff_gin",me->query("max_gin"));
	killer->set("max_gin",me->query("max_gin"));
	
	killer->set("sen",me->query("max_sen"));
	killer->set("eff_sen",me->query("max_sen"));
	killer->set("max_sen",me->query("max_sen"));
	
	killer->set("combat_exp",me->query("combat_exp"));
	killer->set("max_pot",me->query("max_pot"));
 if(killer2){
 copy_hp_item(me,killer2,"kee");
 copy_hp_item(me,killer2,"sen");
 copy_hp_item(me,killer2,"gin");}
if(killer2){
        killer2->set("combat_exp",me->query("combat_exp"));
        killer2->set("max_pot",me->query("max_pot"));}
	set_all_skill(killer,me->query("max_pot")-130);
if(killer2)
        set_all_skill(killer2,me->query("max_pot")-130);
	killer->start_busy(1);
        me->start_busy(1);
        killer->set_temp("apply/armor",50+random(50));
	killer->move(environment(me));
if(killer2){
	killer2->set_temp("apply/armor",50+random(50));
        killer2->move(environment(me));}
	message_vision("$N大声喊道:老子正缺盐呢，你就乖乖地拿命来吧!\n",killer);
	killer->set_leader(me);
if(killer2)
        killer2->set_leader(me);
	killer->kill_ob(me);
if(killer2)
        killer2->kill_ob(me);
	call_out("dao_go",300,killer);
        call_out("dao_go",302,killer2);
return;
}

void dao_go(object ob)
{
        if(!objectp(ob)) {return;}
	message_vision("$N四下看看，急忙走了！\n",ob);
	destruct(ob);
    return;
}

int clean_up()
{
   return 0;
}


