
inherit F_VENDOR_SALE;
void create()
{
   reload("ca_zhang");
   set_name("张先生",({ "zhang xiansheng","zhang","xiansheng" }) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "这是长安的名医张先生，每天有很多人来这里看病。\n");
    set("shop_id",({ "zhang xiansheng","zhang","xiansheng" }) );  
   set("combat_exp", 200000);
   set("str", 28);
   set("per", 22);
   set("attitude", "friendly");
   set("vendor_goods",([
	   "buxuedan":__DIR__"obj/buxuedan",
	   "yangjingdan":__DIR__"obj/yangjingdan",
	   "yao": "/d/clone/obj/medicine/jinchuang",
                "dan": "/d/clone/obj/medicine/dan",
                "yangjing-dan": "/d/clone/obj/medicine/yangjing-dan",
   ]));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int regenerate()
{
        set("called", 0);
        return 1;
}
