
inherit NPC;

void create()
{
   set_name("一群官兵",({ "fighter" }) );
      //  set("gender", "男性" );
       // set("age", 32);
   set("long", "这是一群名骁勇善战的士兵。看起来有一百人左右\n");
       
   set("combat_exp",200);
   set("str", 20);
   set("per", 20);
   set("kee",800);
   set("max_kee",800);
   set("attitude", "peaceful");
   setup();
   carry_object(__DIR__"obj/junfu")->wear();
   carry_object(__DIR__"obj/gangjian")->wield();
  
}

