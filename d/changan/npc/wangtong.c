
inherit NPC;

int change_name();

void create()
{
   set_name("王通",({ "wang tong","wang","tong" }) );
   set("title","当代大儒");
   set("gender", "男性" );
   set("age", 48);
   set("long", "面前的这位老儒生身穿长衫，星霜两鬓，使人知道他年纪定巳不少，
但相貌只是中年模样，且一派儒雅风流，意态飘逸，予人一种超凡
脱俗的感觉。\n");
   set("combat_exp",60000);
   
   set("inquiry",([
     "改名":(:change_name:),
   
   ]));
  
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
   
}

void init()
{
 
   add_action("do_change","zhuanhuan");
  
}

int change_name()
{
   object ob;
   int cost;
   
   ob=this_player();
   
   if(time()-ob->query("change_name/busy_time")<3600*10){
     command("say 你如此频繁地改动自己的名字，如何能真正体会人世间的苦乐？");
     return 1;
   }
   cost=1000000+ob->query("change_name/times")*1000000;
   
   cost=MONEY_D->player_pay(ob,cost);
   
   if(cost==0||cost==2){
     command("say 你要从这个世界消失，改名换姓，不牺牲一点金钱是不行的！\n");
     return 1;
   }
   
   ob->set_temp("can_change_name",1);
   
   command("say 请你用 zhuanhuan 新名字 来更改自己的名字吧！\n");
   
   return 1;
   
}

int do_change(string arg)
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("can_change_name"))
   return notify_fail("你要从这个世界消失，改名换姓，不牺牲一点金钱是不行的！\n");
  
  if(!arg)
  return notify_fail("你的新名字是什么？\n");
  
  if(!LOGIN_D->check_legal_name(arg)){
    command("say 请使用合乎这个江湖规矩的名字吧！\n");
    return 1;
  }
  
  command("rumor "+ob->name()+"这个人从江湖上消失了，而出现了另一个名叫"+arg+"的人！");
  
  tell_object(ob,"你的新名字是「"+arg+"」\n");
  
  ob->set("name",arg);
  
  ob->delete_temp("can_change_name");
  ob->add("change_name/times",1);
  ob->set("change_name/busy_time",time());
  
  return 1;
  
}
