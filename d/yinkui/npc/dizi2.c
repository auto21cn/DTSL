
inherit NPC;

void create()
{
   set_name("弟子",({ "di zi","di","zi" }) );
        set("gender", "女性" );
		
        set("age", 22);
   set("long", "这是阴癸派的弟子。\n");
       
   set("combat_exp",40000);
   set("per", 25);
   set_skill("unarmed",60);
   set_skill("dodge",60);
   set_skill("parry",60);
   set_skill("force",60);
   set_skill("sword",60);
   set_skill("tianmo-dafa",60);
   set_skill("tianmo-jianfa",60);
   set_skill("tianmo-huanzong",60);
   set("gin",300);
   set("max_gin",300);
   set("kee",300);
   set("max_kee",300);
   set("sen",300);
   set("max_sen",300);
   set("force",300);
   set("max_force",300);
   create_family("阴癸派",7,"弟子");
   set("chat_chance",40);
   set("chat_msg",({
    "弟子低声道：做人就是要心狠手辣，宁可我负天下人，不让天下人负我！\n",
    "弟子伸了伸腰：每天都让我守门，什么时候我能学到高超的武功呢？\n",
    "弟子悄声道：据说阴癸派准备加入天下的大战，这下我可有用武之地了！\n",
   }));
   setup();
   carry_object(__DIR__"obj/caiyi")->wear();
   carry_object(__DIR__"obj/changjian")->wield();
  
}
