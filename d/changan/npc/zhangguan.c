// 大唐双龙传


inherit NPC;

void create()
{
  set_name("长官", ({"zhang guan","guan"}));
  set("long","这是长安东市署的长官。\n");
  set("gender", "男性");
  set("combat_exp",200000);

  set_skill("unarmed", 10);
  set_skill("dodge", 40);
  set_skill("parry", 30);
  
  setup();
  carry_object(__DIR__"obj/cloth")->wear();
}

void init()
{
   object ob;
   
   ob=this_player();
   
   if(!ob||is_fighting()) return;
   
   remove_call_out("welcome");
   call_out("welcome",1,ob);
   
}

void welcome(object ob)
{
   if(!ob) return;
   if(environment(ob)!=environment(this_object()))
   return;
   
   switch(random(2)){
    case 0:
     command("say 谁敢以假冒真，粗制滥造，短斤少两者，我一律严惩！！");
     break;
    case 1:
     command("say 我办事绝对公正，有什么不平的事到我这里来说就好了。");
   }
   
}

