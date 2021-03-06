#include <ansi.h>

inherit NPC;
inherit F_MASTER;

int do_action1();
int do_action2();
int do_action3();

void create()
{
   int i;
   object *ob;
   
   set_name("候希白",({ "hou xibai","hou"}) );
   set("gender", "男性" );
   set("age", 26);
   set("long", "这是花间派的高手，也是花间派的唯一传人。\n");
    set("combat_exp",3000000);
   set("per", 26);
   
    set_skill("dodge",400);
    set_skill("parry",400);
    set_skill("force",400);
    set_skill("strike",400);
    set_skill("blade",400);
    set_skill("sword",400);

    set_skill("flower-force",400);
    set_skill("luohua-step",400);
    set_skill("zhehua-baishi",400);
    set_skill("baihua-zhang",400);
    set_skill("busi-yin",200);
    set_skill("huachan",400);
    set_skill("literate",400);

    set("apply_points",1000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: command("perform baihua") :),
        (: command("perform zhi") :),
        (: command("exert feihua") :),
        (: command("exert liushui") :),
        (: command("execute xihua") :),
    }));
    set("max_gin",3000);
    set("max_sen",4000);
    set("max_kee",5000);
    set("max_force",7000);
    set("force",7000);
    set("jiali",100);

   create_family("花间派",5,"传人");
   
   set("inquiry",([
        "不死印":(:do_action1:),
        "折花百式":(:do_action2:),
        "花间十二支":(:do_action3:),
       ]));
   
    setup();
    carry_object("/d/yangzhou/npc/obj/chouyi")->wear();
   
   ob=children(__DIR__"obj/tieshan");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"你手中的"+ob[i]->query("name")+"被它的主人收回去了！\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"被一阵风卷走了。\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
   carry_object(__DIR__"obj/tieshan")->wield();
}

string long()
{
   if(this_player()->query_temp("bai_huajian/step2")||
      this_player()->query("family/family_name")=="花间派"){
       return query("long");
   }
   else
   return "据说他是一位武林高手，而且善于书画。\n";
}

void attempt_apprentice(object ob)
{   
	if(ob->query("family"))
	if(ob->query("family/family_name")=="花间派")
	if((int)ob->query("family/generation",1)<=5){
	   command("say 这话从何说起？");
	   return;	
	
        }
        if(ob->query("gender")=="女性"){
          command("say 花间派的武功不适合女子修炼，你还是算了！");
          return;
        }
	if(ob->query("per")<25)
	{
		tell_object(ob,"候希白为难道：你的相貌，唉，叫我怎么收你为徒？\n");
		return;
	}
	if(!ob->query_temp("bai_huajian/step2")){
	  command("say 我侯希白怎么能轻易收徒？");
	  return;
	}
	
	ob->set("huajian_menpai/huajian_MKS",ob->query("MKS"));
        ob->set("huajian_menpai/huajian_PKS",ob->query("PKS"));
        ob->set("huajian_menpai/huajian_deadtimes",ob->query("deadtimes"));
	
	
	command("say 好，我花间派从此又多了一个传人！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "hua1");
}

int accept_object(object ob,object obj)
{
   string msg;
   
   if(!obj->id("steal_busiyin_obj"))
   return 0;
   if(ob->query("execute_quest/busiyin"))
   return 0;
   
   msg="$N笑道：这是本派的秘籍不死印啊！谢谢你把它给了我！\n"+
       "既然你立志学习不死印，那你以后就和我学习不死印吧！\n";
   
   message_vision(msg,this_object());
   ob->set("execute_quest/busiyin",1);
   return 1;
}

int do_action1()
{
   object ob;
   
   ob=this_player();
   
   if(ob->query("family/family_name")!="花间派"){
     command("say 这是本派的秘密，可不能告诉你。");
     return 1;
   }
   if(ob->query("execute_quest/busiyin")){
     command("say 不死印是我花间派的绝学，你要好好学习。");
     return 1;
   }   
   if(present("steal_busiyin_obj",ob)){
     command("say 你手上拿的什么东西？给我看看。");
     return 1;
   }
   ob->set_temp("steal_busiyin/action0",1);
   command("say 不死印是花间和补天阁两派心法和佛门心法综合的一门绝学，我现在和\n"+
           "石师的补天阁传人杨虚彦争夺不死印卷，现在一人拿了一半。");
   return 1;
}

int do_action2()
{
   object ob,obj;
   string msg;
   
   ob=this_player();
   
   if(ob->query_skill("zhehua-baishi",1)<160){
     command("say 你的折花百式修为太低了，还无法领会其中的诀窍！");
     return 1;
   }
   if(ob->query_skill("huachan",1)<160){
     command("say 你的画禅心法太低了，还无法领会折花百式的诀窍！");
     return 1;
   }
   if(ob->query("execute_quest/busiyin")){
     command("say 你学习了不死印，无法再领会折花百式诀窍的！");
     return 1;
   }
   if(present("perform_quest_zhehuabaishi_obj",ob)){
     command("say 你还是快去画画吧！");
     return 1;
   }
   if(ob->query("perform_quest/zhi_times")>=3){
     command("say 你已经领会我们花间的追求美好事物的意境，很好啊！");
     return 1;
   }
   obj=new(__DIR__"obj/shanzi");
   obj->move(ob);
   msg="$N给了$n一"+obj->query("unit")+obj->query("name")+"。\n";
   message_vision(msg,this_object(),ob);
   command("say 花间派重在领会世间的美好事物，你去拿这个扇子去画三个女子的象吧！");
   return 1;
}

int do_action3()
{
  object ob;
  
  ob=this_player();
  
  if(ob->query_skill("zhehua-baishi",1)<160){
     command("say 你的折花百式修为太低了，还无法领会其中的诀窍！");
     return 1;
   }
   if(ob->query_skill("huachan",1)<160){
     command("say 你的画禅心法太低了，还无法领会折花百式的诀窍！");
     return 1;
   }
   if(ob->query("execute_quest/busiyin")){
     command("say 你学习了不死印，无法再领会折花百式诀窍的！");
     return 1;
   }
   
   if(ob->query("perform_quest/zhi_times")<3){
     command("say 你还没有领会我们花间的追求美好事物的意境，如何领会这么高深的功夫！");
     return 1;
   }
   
   ob->set_temp("perform_quest/zhi_action1",1);
   command("say 花间十二支是花间的最后绝技，我也不太懂。你去找石师问一下吧！");
   
   return 1;
}
