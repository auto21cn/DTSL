// 大唐双龙传

//傅君瑜


inherit F_MASTER;
inherit NPC;

#include <ansi.h>

int do_jiejiu(string arg);

void create()
{
  set_name("傅君瑜", ({"fu junyu", "fu", "junyu"}));
  set("gender", "女性");
 
  set("per",26);
  set("max_kee",3000);
  set("max_gin",3000);
  set("max_sen",3000);
  set("max_force",3000);
  set("force",3000);
  set("combat_exp",800000);
 
  set_skill("literate",200);
  set_skill("sword", 200);
  set_skill("force", 200);
  set_skill("dodge", 200);
  set_skill("parry", 200);
  
  set_skill("jiuxuan-dafa",200);
  set_skill("yijian-shu",200);
  set_skill("jiuzhuan-jianjue",200);
  set_skill("xingyun-dodge",200);
 
  setup();
  
  create_family("弈剑派",3, "弟子");
  carry_object(__DIR__"obj/sword");

}

void attempt_apprentice(object ob)
{
     
     int lev;
     
     if(ob->query_skill("jiuxuan-dafa",1)<100){
       command("say 你的九玄大法修为不够，我可不要这样的徒弟！");
       return;
     }
     
     if(ob->query("office_number")<30){
       command("say 你的功绩太低了，我可不要这么懒惰的弟子！");
       return;
     }
     
     if(!ob->query("yjp/family2")){       
       lev=ob->query_skill("leg",1);
       lev=lev*lev/(lev+100);
       ob->party_reward_skill("sword",lev);
       tell_object(ob,HIY"你从基本腿法中领略到了基本剑法！\n"NOR);

     }
     ob->set("yjp/family2",1);
               
     command("say 我们弈剑派的武功博大精深，你可要好好学习！");
     
     command("recruit " + ob->query("id") );
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "yijian2");
}