
inherit NPC;
#include <ansi.h>
#include <org.h>

void create()
{
   set_name("韩盖天",({ "han gaitian","han","gaitian" }) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "这是海沙帮的帮主。\n");
       
   set("combat_exp", 5000);
   set("str", 24);
    set("attitude", "friendly");
    set("shili",([
       "name":"haisha_b",
       "leader":"haisha_b",
       ]));
    set("shili_id","haisha");
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}
int accept_enroll(object me)
{
	object ob;
	ob=this_object();
	if(me->query("shili"))
	if(me->query("shili/name")!=ob->query("shili/name"))
	 return notify_fail("我们海杀帮可不要其他帮派的人！\n");
	if(!ob->query("shili/leader"))
	 return notify_fail("我已经不是帮主了，和我说没用的！\n");
	if(me->query("shili/name")==ob->query("shili/name"))
	 return notify_fail("你高声喊道：海杀帮天下无敌！\n");
	me->set_temp("mark_join",ob->query("shili/name"));
	message_vision("$N朝$n笑道：希望$n能好好干，使我们海杀帮雄霸江南！\n",ob,me);
	tell_object(me,HIW"\n请去势力名单榜处打 "HIG"join"HIW" 命令就算加入了！\n\n"NOR);
	
	return 1;
}

int accept_gage(object me)
{
   this_object()->fight_ob(me);
   me->fight_ob(this_object());
   return 1;
}