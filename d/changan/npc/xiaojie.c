
inherit NPC;

void create()
{
   set_name("小姐",({ "xiao jie","xiao","jie" }) );
        set("gender", "女性" );
        set("age", 22);
   set("long", "这是一位在长安城闲逛的小姐。\n");
       
   set("combat_exp", 2000);
   set("str", 18);
   set("per", 22);
   set("attitude", "friendly");
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

