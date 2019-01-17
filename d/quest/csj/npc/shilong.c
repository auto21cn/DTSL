
inherit NPC;
#include <ansi.h>

int do_action1();

void create()
{
   object *ob;
   int i;
   
   set_name("石龙",({ "shi long","shi","long"}) );
   set("gender", "男性" );
   set("title","推山手");
   set("age", 32);
   set("long","他是就是扬州武功最高的石龙。\n");
   set("max_kee",600);
   set("max_gin",100);
   set("max_sen",100);
   set("max_force",100);
   set("force",100);
   set("combat_exp",1);
   set("inquiry",([
      "长生诀":(:do_action1:),
      ]));
    setup();
   
   ob=children(__DIR__"tianwen");
   for(i=0;i<sizeof(ob);i++)
    if(objectp(ob[i])&&environment(ob[i]))
     destruct(ob[i]);
  
}

int do_action1()
{
  object ob;
  
  ob=this_player();
  
  if(ob->query("dtsl_quest_csj_help_ok")){
    command("say 我可没有这个东西！");
    return 1;
  }
  
  command("say 既然你晓得我的秘密，我不会留下活口了！");
  ob->set_temp("kill_shilong",1);
  ob->set("dtsl_quest_csj_help_ok",1);
  kill_ob(ob);
  return 1;
}

int chat()
{
  object ob,target;
  
  ob=query_temp("last_damage_from");
  
  if(!ob||!ob->query_temp("kill_shilong"))
   return ::chat();
   
  if(query("eff_kee")*100/query("max_kee")<20){
     target=new(__DIR__"tianwen");
     target->move("/d/yangzhou/guangchang");
     command("say 哼，你还真有点本事！！");
     message_vision("$N一转身跑了！！\n",this_object());
     destruct(this_object());
     return 1;
  }
  return ::chat();
}