
inherit NPC;

void create()
{
   set_name("镖师",({ "biao shi","biao","shi" }) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "这是威远镖局的镖师。\n");
       
   set("combat_exp", 90000);
   set("str", 28);
   set("per", 23);
   set("attitude", "peaceful");
   set_skill("unarmed",70);
   set_skill("parry",70);
   set_skill("dodge",70);
   set_skill("force",70);
   set("max_force",200);
   set("force",200);
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

