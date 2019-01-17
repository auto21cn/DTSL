
inherit NPC;

void create()
{
   set_name("老者",({ "lao zhe","lao","zhe","old"}) );
   set("gender", "男性" );
   set("age", 62);		
   set("long", "这是在扬州城居住的的老者。\n");
       
   set("combat_exp", 5000);
   set("per",15);	
   set_skill("unarmed",20);
   set_skill("dodge",20);
   set_skill("parry",20);
   set("attitude", "peaceful");
   
   set("chat_chance",10);
   set("chat_msg",({
   	(:do_command,"chitchat":),
   	(:do_command,"dream2":),
   	(:do_command,"fakuan":),
   }));
   	
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
 
}

