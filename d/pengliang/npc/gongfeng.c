
inherit NPC;
inherit F_DEALER;

void create()
{
   set_name("供奉",({ "gong feng","gongfeng","gong" }) );
        set("gender", "男性" );
        set("age", 40);
   set("long", "这是当铺的供奉，对人典卖东西是出了名的小气。\n");
       
   set("combat_exp",300000);
   set("str",26);
   set("per", 22);
   set("force",500);
   set("max_force",500);
   set("kee",800);
   set("max_kee",800);
   set("sen",500);
   set("max_sen",500);
   set_skill("dodge",80);
   set_skill("parry",80);
   set_skill("unarmed",80);
   set("attitude", "peaceful");
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

void init()
{
	add_action("do_list","list");
	add_action("do_buy","buy");
	add_action("do_value",({"value","gujia"}));
	add_action("do_sell",({"sell","mai"}));
}

