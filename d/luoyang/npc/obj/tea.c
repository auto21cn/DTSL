
inherit ITEM;

void create()
{
   set_name("黄芽叶", ({ "huang yaye","tea","yaye"}) );
   set_weight(1000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("long","这是茶中极品黄芽叶。\n");
     set("unit", "包");
     set("value", 60);
     set("no_sell",1);
     set("order",1);
     set("nogive_player",1);
  }
   setup();
}
