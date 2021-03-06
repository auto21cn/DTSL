
inherit F_MASTER;
inherit NPC;

#include <ansi.h>
#include <job_money.h>

string do_action1();

void create()
{
   set_name("林士宏",({ "lin shihong","lin" }) );
        set("gender", "男性" );		
        set("age", 34);
   set("long", "他就是鄱阳会会主新近自称楚帝的林士宏。\n");
       
   set("combat_exp",300000);
  
   set_skill("dodge",100);
   set_skill("parry",100);
   set_skill("force",100);
   set_skill("strike",100);
   
   set_skill("jiutian-huanzhang",100);
   set_skill("literate",100);
   set_skill("tianmo-dafa",100);
   set_skill("tianmo-huanzong",100);
   set_skill("tianmo-jue",100);
  
   set("max_gin",1000);
   set("max_kee",1000);
   set("max_sen",1000);
   set("force",1000);
   set("max_force",1000);
   create_family("阴癸派",7,"弟子");
   set("class","yin1");
   set("inquiry",([
     "阴癸派":(:do_action1:),
     ]));
   setup();
   
}

int accept_object(object who,object obj)
{
   if(!obj->query("yinguibaishimihan"))
    return 0;
   if(who->query("gender")=="女性")
   return notify_fail("这样东西给我不太合适，你还去找旦梅吧！\n");
   who->set_temp("bai_yingui/step2",1);
   tell_object(who,query("name")+"嘿嘿一笑：原来是郑兄推荐来的人才，好，好！！\n"+
   "如果你不嫌弃，就拜我为师吧！\n");
   return 1;
}
   

void attempt_apprentice(object ob)
{   
	if(ob->query("family"))
	if(ob->query("family/family_name")=="阴癸派")
	if((int)ob->query("family/generation",1)<=7)
	{   
	   command("say 此话从何说起？\n");
	   return;
	}
	
	if(ob->query("gender")=="女性"){
	
	command("say 我不收女弟子的！你如果诚心投入本派，去找旦梅吧！\n");
	return;
        }
        
        if(!ob->query_temp("bai_yingui/step2")){
        command("say 你当我是什么人？怎么能随便收徒弟？");
        return;
        }
	
	ob->delete_temp("bai_yingui/step2");
	ob->delete_temp("bai_yingui/step1");
	
	command("say 好！希望你将来能一统魔道，长我阴癸派名声！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "none");
}

string *dirs=({
"/d/huashan",
});

string do_action1()
{
   object ob,target;
   
   ob=this_player();
   
   if(ob->query("family/family_name")!="阴癸派")
   return "这也是你打听的吗？快走开！\n";
   
   if((int)ob->query("family/generation",1)<=7)
   return "你对本派已经知道很多了，还问我做什么？\n";
   
   if(ob->query_skill("tianmo-dafa",1)<100)
   return "你的天魔大法修为太低了，还是先别问太多本派的事了吧！\n";
   
   if(ob->query_temp("bai_yingui/step3"))
   return "如果你不能“斩俗缘”，就永远不能成为真正的阴癸弟子！！\n";
   
   if(ob->query_temp("bai_yingui/step4")||
      ob->query("yingui_pass_ok")){
   ob->set("yingui_pass_ok",1);
   ob->delete_temp("bai_yingui/step4");
   return "既然你已经“斩俗缘”，那么去阴癸密地去拜师吧！\n"+
          "在洛阳附近有个小村子，在村子里面钻个草丛就可以了！\n";
   }
   
   target=new(__DIR__"qinren");
   
   if(!random_place(target,dirs))
   return "等会，等会... ...\n";
   if(!environment(target))
   return "等会，等会... ...\n";
   
   target->set("long","这是"+ob->name()+"的亲生"+target->query("name")+"。\n");
   target->set("name",ob->name()+"的"+target->query("name"));
   target->set("target_id",ob->query("id"));
   ob->add_temp_array("job_temp_killer",target);
   
   ob->set_temp("bai_yingui/step3",1);
   
   return "好吧，我的本事你都学到了！\n"+
   "如果想继续学习魔功，要成为“人级”弟子才可以！\n"+
   "本派有规矩叫“斩俗缘”！我已经找到了你的亲人，\n"+
   "据说"+target->query("gender_id")+"在"+MISC_D->find_place(environment(target))+"，你去把"+
   target->query("gender_id")+"给杀了！！\n";
}