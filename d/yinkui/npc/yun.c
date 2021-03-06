

inherit NPC;

#include <ansi.h>

string do_quest1();
string do_quest2();
string do_quest3();

void create()
{
   set_name("云长老",({ "yun zhanglao","yun" }) );
        set("gender", "男性" );
		
        set("age", 42);
   set("long", "他就是阴癸派的云长老，他的邪功可以说的上是一流。\n");
       
   set("combat_exp",600000);
  
   set_skill("dodge",180);
   set_skill("parry",180);
   set_skill("force",180);
   set_skill("strike",180);
   set_skill("cuff",180);
   set_skill("jiutian-huanzhang",180);
   set_skill("linglong-yuquan",180);
   set_skill("literate",180);
   set_skill("tianmo-dafa",180);
   set_skill("tianmo-huanzong",180);
   
   set("max_gin",1500);
   set("max_kee",1500);
   set("max_sen",1500);
   set("force",2000);
   set("max_force",2000);
   create_family("阴癸派",5,"长老");
   set("inquiry",([
   "天魔阵":(:do_quest1:),
   "茶叶":(:do_quest2:),
   "香料":(:do_quest3:),
   ]));
   setup();
   
}

string do_quest1()
{
   object ob;
  
  ob=this_player();
  
  if(ob->query("perform_quest/yulong"))
  return "你已经掌握了天魔带的精髓，无法学习天魔阵了！\n";
  
  if(ob->query("perform_quest/wanhuan"))
  return "你已经掌握了千变铜箫的精髓，无法学习天魔阵了！\n";
  
  if(ob->query("perform_quest/lingxiao"))
  return "你已经掌握了天魔斩的精髓，无法学习天魔阵了！\n";
    
  if(ob->query("class")!="yin3")
  return "你还不够资格问这个问题！\n";
  
  if(ob->query_temp("tmz_quest/pass_yun"))
  return "你的功夫我已经考验过了，你去问其他长老吧！\n";
  
  ob->set_temp("tmz_quest/yun_step1",1);
  
  return "想学天魔阵？先打败我再说吧！\n";
}

int surrender(object killer,object victim)
{
   if(!killer->query_temp("tmz_quest/yun_step1"))
   return 1;
   killer->delete_temp("tmz_quest/yun_step1");
   killer->set_temp("tmz_quest/yun_step2",1);
   
   message_vision(CYN"\n$N"+CYN+"脸色一变，朝$n"+CYN+"道："+RANK_D->query_respect(killer)+"果然身手不凡！\n"+
   "不过你还要给我办点事情才可以！\n"NOR,victim,killer);
   return 1;
}

string do_quest2()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("tmz_quest/yun_step2"))
  return "我又不是卖茶叶的，你问我这个问题做什么？\n";
  
  ob->set_temp("tmz_quest/yun_buy_tea",1);
  
  return "祝尊者要喝的黄芽叶，你去给我找来，要求挺直匀齐，色泽黄中带\n"+
         "绿，细嫩如亳，形似鸭舌，是这茶叶的极品。\n";
}

string do_quest3()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("tmz_quest/yun_step2"))
  return "我又不是卖香料的，你问我这个问题做什么？\n";
  
  ob->set_temp("tmz_quest/yun_buy_xiangliao",1);
  
  return "婠婠姑娘要的香料，你去给我找来，记住，是要从丹桂花提炼制成的香料。\n";

}

int get_quest_obj1(object who,object obj)
{
   if(!obj->query("super_tea")){
     command("kok "+who->query("id"));
     return notify_fail("这是什么破烂茶叶？？祝尊者会喝这样的茶叶吗？？\n");
   }
   who->delete_temp("tmz_quest/yun_step2");
   who->add_temp("tmz_quest/yun_need_goods",1);
   
   if(who->query_temp("tmz_quest/yun_need_goods")>=2){
     who->delete_temp("tmz_quest/yun_need_goods");
     who->set_temp("tmz_quest/pass_yun",1);
     tell_object(who,"\n"+query("name")+"一笑：我的考验你通过了！至于其他长老，\n"+
     "你去问问他们吧！\n");
     return 1;
   }
   return 1;
}

int get_quest_obj2(object who,object obj)
{
   if(!obj->query("quest_order")){
     command("kok "+who->query("id"));
     return notify_fail("这是什么破烂香料？？婠婠姑娘会要这样的东西吗？？\n");
   }
   who->delete_temp("tmz_quest/yun_step2");
   who->add_temp("tmz_quest/yun_need_goods",1);
   
   if(who->query_temp("tmz_quest/yun_need_goods")>=2){
     who->delete_temp("tmz_quest/yun_need_goods");
     who->set_temp("tmz_quest/pass_yun",1);
     tell_object(who,"\n"+query("name")+"一笑：我的考验你通过了！至于其他长老，\n"+
     "你去问问他们吧！\n");
     return 1;
   }
   return 1;
}
    

int accept_object(object who,object obj)
{
   if(!obj->query("order"))
   return 0;
   
   if(obj->query("order")==1)
    return get_quest_obj1(who,obj);
   else
    return get_quest_obj2(who,obj);
}