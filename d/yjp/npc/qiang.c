// 大唐双龙传

//qiang.c 傅君嫱

inherit F_MASTER;
inherit NPC;

#include <ansi.h>

void create()
{
  set_name("傅君嫱", ({"fu junqiang", "fu", "junqiang"}));
  set("title", "弈剑派亲传弟子");
  set("gender", "女性");
  set("age", 23);
  set("str", 30);
  set("int", 25);
  set("per", 30);
  set("max_kee",1000);
  set("max_gin",1000);
  set("max_sen",1000);
  set("max_force",1000);
  set("force",1000);
  set("combat_exp",100000);
  set_skill("leg",100);
  set_skill("literate", 100);
  set_skill("force", 100);
  set_skill("dodge", 100);
  set_skill("parry", 100);
  
  set_skill("jiuxuan-dafa",100);
  set_skill("fengxue-leg",100);
  set_skill("xingyun-dodge",100);
  set_skill("yijian-shu",100);
 
  setup();
  
  create_family("弈剑派",4, "弟子");

}

void attempt_apprentice(object ob)
{
     
     if(!ob->query_temp("bai_yjp_action4")){
       command("say 我可不是轻易收弟子的！");
       return;
     }
     
     ob->set("yjp/family1",1);
     
     command("say 我们弈剑派的武功博大精深，你可要好好学习！");
     
     command("recruit " + ob->query("id") );
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "yijian1");
}