
inherit NPC;

void create()
{
   set_name("侠客",({ "xia ke","ke","xia" }) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "这是一位侠客，看起来是要争夺和氏璧来了。\n");
       
   set("combat_exp", 200000);
   set("str", 22);
   set("per", 18);
   set("attitude", "peaceful");
   set("blade",({"whdmdao"}));
   set_skill("whdmdao",70);
   set_skill("parry",70);
   set_skill("unarmed",70);
   set_skill("parry",70);
   set_skill("dodge",70);
   set_skill("force",70);
   set_skill("blade",80);
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
   carry_object(__DIR__"obj/blade")->wield();
  
}

void init()
{
	object ob,ob2;
	ob=this_player();
	ob2=this_object();
	::init();
	if(!ob||!present(ob,environment())||ob2->is_fighting()) return;
	call_out("welcome",1,ob,ob2);
	
}

void welcome(object ob,object ob2)
{
   if(!ob||!present(ob,environment())||ob2->is_fighting()) return;
	switch(random(2))
	{
	case 0: message_vision("$N警惕地向四周看了看!\n",ob2);break;
	case 1: message_vision("$N上上下下打量了$n几眼.\n",ob2,ob);
	}
	remove_call_out("welcome");
	return;
}
