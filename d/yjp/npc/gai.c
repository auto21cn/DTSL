// 大唐双龙传

inherit F_MASTER;
inherit NPC;

#include <ansi.h>

int do_action1();
int do_action2();
int do_action3();

void create()
{
  set_name("盖苏文", ({"ge suwen", "ge", "suwen"}));
  set("nickname", "五霸刀");
  set("gender", "男性");
  set("age", 36);
  set("str",30);
  set("per",24);
  set("max_kee",3000);
  set("max_gin",3000);
  set("max_sen",3000);
  set("max_force",3000);
  set("force",3000);
  set("combat_exp",1000000);
  set_skill("blade",200);
  set_skill("literate",200);
  set_skill("force",200);
  set_skill("dodge",200);
  set_skill("parry",200);
  
  set_skill("jiuxuan-dafa",200);
  set_skill("yijian-shu",200);
  set_skill("wuba-daofa",200);
  set_skill("xingyun-dodge",200);
  
  set("inquiry",([
     "沉香":(:do_action1:),
     "五刀赌约":(:do_action2:),
     "统一高丽":(:do_action3:),
     ]));
  set("perform_quest/sanfen",1);
  setup();
  
  create_family("弈剑派", 3, "弟子");
  carry_object(__DIR__"obj/blade")->wield();
}

void init()
{
  add_action("do_answer","answer");

}

void attempt_apprentice(object ob)
{
     
     if(ob->query_skill("jiuxuan-dafa",1)<160){
       command("say 你的九玄大法修为不够，我可不要这样的徒弟！");
       return;
     }
     if(ob->query_skill("blade",1)<160){
       command("say 你的基本刀法修为不够，我可不要这样的徒弟！");
       return;
     }
     if(ob->query("office_number")<60){
       command("say 你的功绩太低了，我可不要这么懒惰的弟子！");
       return;
     }
         
     ob->set("yjp/family2",1);
     
     command("say 你可要好好学习武艺，将来助我一统高丽！");
     
     command("recruit " + ob->query("id") );
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "gaoli2");
}

int do_action1()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("bai_fu_action1")){
    command("say 这块沉香可是弈剑大师的至爱，我打算送给他作为支持我打江山的礼物。");
    return 1;
  }
  ob->delete_temp("bai_fu_action1");
  ob->set_temp("bai_fu_action2",1);
  command("say 这块沉香可是弈剑大师的至爱，我打算送给他作为支持我打江山的礼物。");
  return 1;
}

int do_action2()
{
   object ob;
  
   ob=this_player();
   
   if(is_fighting()){
     command("say 我正打仗呢，你没看到吗？等会吧！");
     return 1;
   }
   
   if(!ob->query_temp("bai_fu_action2")){
     command("say 凭你也配和我定五刀赌约吗？");
     return 1;
   }
   ob->set_temp("bai_fu_action3",1);
   command("say 当年少帅以五刀赌约逼我退出长安之事，我输的心服口服。\n"+
           "今天我也想重温一下，你若能挡我五刀之威，这沉香就送你。");
   fight_ob(ob);
   set("apply_points",300);
   command("perform sanfen");
   remove_call_out("do_fight");
   call_out("do_fight",8,ob);
   return 1;
}

void do_fight(object ob)
{
   object obj;
   string msg;
   
   if(!ob) return;
   if(!living(ob)) return;
   if(ob->is_ghost()) return;
   if(!ob->is_fighting(this_object())) return;
   if(environment(ob)!=environment(this_object())) return;
   
   remove_enemy(ob);
   ob->remove_enemy(this_object());
   ob->delete_temp("bai_fu_action2");
  
   
   command("say 好，你确实武功不凡，我就给了你这个沉香！");
   ob->delete_temp("bai_fu_action3");
   ob->set_temp("bai_fu_action4",1);
   
   obj=new(__DIR__"obj/chenxiang");
   obj->move(ob);
   msg="$N给了$n一"+obj->query("unit")+obj->query("name")+"。\n";
   message_vision(msg,this_object(),ob);
   return;
}

int do_action3()
{
   object ob;
   
   ob=this_player();
   
   if(ob->query("perform_quest/sanfen")){
     command("say 你已经掌握了五霸刀法的精髓，自己去提高吧！");
     return 1;
   }
   if(ob->query("perform_quest/xingchen")){
     command("say 你已经掌握了九转剑诀的精髓，无法在领会五霸刀法的精髓！");
     return 1;
   }
   if(ob->query_skill("wuba-daofa",1)<160){
     command("say 你的五霸刀法修为太低，无法掌握其中的精髓！");
     return 1;
   }
   if(ob->query("perform_quest/sanfen_fail")){
     command("say 你当我说的话是什么？你再也休想学到五霸刀法的精髓！！");
     return 1;
   }
   ob->set_temp("perform_quest/sanfen_action",1);
   command("say 我以统一高丽为自己的人生目标，你会不会辅助我？");
   return 1;
}

int do_answer(string arg)
{
   object ob;
   
   ob=this_player();
   
   if(!ob->query_temp("perform_quest/sanfen_action"))
   return 0;
   if(!arg||
       (arg!="同意"&&arg!="不同意")
     )
   return notify_fail("你是 同意 还是 不同意 ？\n");
   if(arg=="同意"){
     ob->delete_temp("perform_quest/sanfen_action");
     ob->set("perform_quest/sanfen",1);
     command("say 好！我这就传授你五霸刀法的精髓之处！\n");
     message_vision("$N凑到$n耳边低语了几句，$n若有所悟，点了点头！\n",this_object(),ob);
     return 1;
   }
   ob->delete_temp("perform_quest/sanfen_action");
   ob->set("perform_quest/sanfen_fail",1);
   command("say 好！那你一辈子也休想学到我的五霸刀法精髓之处！！！");
   return 1;
}