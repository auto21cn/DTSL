
inherit NPC;
#include <ansi.h>

mapping f_name=([
"阴癸派":"慈航静斋",
"慈航静斋":"阴癸派",

"宋家堡":"弈剑派",
"弈剑派":"宋家堡",

"花间派":"净念禅院",
"净念禅院":"花间派",

"东溟派":"突厥",
"突厥":"东溟派",
"普通百姓":"净念禅院",

]);

void create()
{
        set_name("莲柔",({ "lian rou","lian","rou"}) );
        set("gender", "女性" );
        set("age", 16);
        set("per",26);
        set("long","她是云帅的女儿，武功已经得到父亲的真传。\n");
        set("combat_exp",400000);
        
        set("max_kee",1000);
        set("max_sen",1000);
        set("max_gin",1000);
        set("max_force",1000);
        set("force",1000);
        set_skill("parry",130);
        set_skill("dodge",130);
        set_skill("force",130);
        
        set_skill("blade",130);
        set_skill("leveltwo-blade",130);
        set_skill("jiuying-dodge",130);
        
        set("daughter","lianrou");
    setup();
  
   carry_object(__DIR__"obj/blade")->wield();
  
}

void init()
{
   add_action("do_jiejiu","jiejiu");
 
}

void unconcious()
{
   object killer;
   
   killer=query_temp("last_damage_from");
   if(!killer) return ::unconcious();
   
   if(!killer->query("family/family_name")) return ::unconcious();
   
   set("hitted_family",killer->query("family/family_name"));
   set("long",query("long")+"她曾经受到过"+killer->query("family/family_name")+"弟子的袭击。\n");
   return ::unconcious();
 
}

int return_home(object home)
{
   return 0;
   
}

int do_jiejiu(string arg)
{
  object ob,target;
  object obj1,obj2;
  string f_msg;
  
  ob=this_player();
  
  if(!arg||!objectp(target=present(arg,environment(ob))))
  return notify_fail("你要解救谁？\n");
  
  if(target!=this_object())
  	return 0;
  
  if(target->query_temp("no_guard")){
    command("say 我已经被人解救了。\n");
    return 1;
  }
  if(ob->query("dtsl_quest_ysdodge_ok")){
    command("bow "+ob->query("id"));
    return 1;
  }
  
  if(!ob->query_temp("kill_lianrou_killer")
    &&present("ren fanzi",environment(ob))){
    command("say 你没有杀死看守我的人贩子，我可不相信你会解救我！\n");
    return 1;
  }
  if(ob->query("dtsl_quest_ysdodge/fail")){
    command("say 我可不用你来救我。\n");
    return 1;
  }
  f_msg=ob->query("family/family_name");
  if(!stringp(f_msg)) f_msg="普通百姓";
  
  if(f_name[f_msg]!=target->query("hitted_family")){
    command("say 我还以为会是"+f_name[target->query("hitted_family")]+"弟子来救我的呢！不过也非常谢谢你了！");
    ob->set("dtsl_quest_ysdodge/fail",1);
    destruct(target);
    return 1;
  }
  
  obj1=new(__DIR__"obj/cangbaotu");
  obj2=new(__DIR__"obj/miji1");
  
  obj1->move(ob);
  obj2->move(ob);
  command("thank "+ob->query("id"));
  message_vision("$N给了$n一"+obj1->query("unit")+obj1->query("name")+"。\n"+
                 "$N给了$n一"+obj2->query("unit")+obj2->query("name")+"。\n",target,ob);
  target->set_temp("no_guard",1);
  call_out("go_out",60,target);
  ob->delete_temp("kill_lianrou_killer");
  return 1;
}

int accept_object(object ob,object obj)
{
   object b_obj;
   
   if(!obj->query("give_lianrou"))
   return 0;
   
   b_obj=new(__DIR__"obj/lianrou_blade");
   b_obj->set("user",ob->query("id"));
   b_obj->move(ob);
   message_vision("$N给了$n一"+b_obj->query("unit")+b_obj->query("name")+"。\n",
    this_object(),ob);
   return 1;
}

void go_out(object target)
{
  if(!target) return;
  message_vision("$N匆匆地走了。\n",target);
  destruct(target);
  return;
}