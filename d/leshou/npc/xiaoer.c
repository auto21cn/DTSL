
inherit F_VENDOR_SALE;
void create()
{
   reload("ls_xiaoer");
   set_name("店小二",({ "xiao er","xiao","er"}) );
        set("gender", "男性" );
        set("age", 20);
   set("long", "这是小吃店的店小二。\n");
    set("shop_id",({ "xiao er","xiao","er"}) );
   set("combat_exp",3000+random(3000));
   set_skill("dodge",80);
   set_skill("parry",80);
   set_skill("unarmed",80);
   set("attitude", "peaceful");
   set("vendor_goods",([
	  "mifan":__DIR__"obj/mifan",
	  "jiudai":__DIR__"obj/jiudai",
	  "kaoya":__DIR__"obj/kaoya",
	  "kaoyangrou":__DIR__"obj/kaoyangrou",
	  "gongbaojiding":__DIR__"obj/gongbao-jiding",
	  "liudoufu":__DIR__"obj/liudoufu",
	  "jiachangliangcai":__DIR__"obj/jiachang-liangcai",
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
