

inherit F_VENDOR_SALE;

void create()
{
    reload("zhensao");
  set_name("贞嫂", ({ "zhen sao","zhen" }) );
  set("shop_id",({ "zhen sao","zhen" }) );
  set("gender", "女性" );
  set("age", 25);
  set("combat_exp", 40000);
  set("attitude", "friendly");
 set("vendor_goods", ([
   "baozi":__DIR__"obj/baozi",
   ]));
  setup();
    carry_object("/d/yangzhou/npc/obj/cloth")->wear();
  
}

void init()
{
  object ob;

  ::init();
  if( interactive(ob = this_player()) && !is_fighting() ) {
    remove_call_out("greeting");
    call_out("greeting", 1, ob);
  }
  add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
  if( !ob || !visible(ob) || environment(ob) != environment() ) return;
  command("say 这位" + RANK_D->query_respect(ob) +"请进请进。");
}

int regenerate()
{
        set("called", 0);
        return 1;
}

