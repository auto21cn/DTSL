
inherit NPC;

void create()
{
   set_name("公子",({ "gong zi","gong","zi"}) );
        set("gender", "男性" );
        set("age", 22);
		
   set("long", "这是扬州城的公子,平时在扬州闲逛。\n");
       
   set("combat_exp", 30000);
   set("str", 26);
   set("per", 22);
   set_skill("unarmed",50);
   set_skill("dodge",50);
   set_skill("parry",50);
  set("attitude", "peaceful");
   set("chat_chance",50);
   set("chat_msg",({
	   "公子微微一笑:有没有漂亮的妹妹,给我认识认识啊!\n",
	   "公子大声道:我家有钱有势,做什么事不行啊!\n",
  }));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
 
}

