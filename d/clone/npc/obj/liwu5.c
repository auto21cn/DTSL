
inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>
void create()
{
   set_name(HIY"鸳鸯泉"NOR, ({"yuanyang quan"}));
   set_weight(30);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("long", "这是武林侠侣结婚用来招待客人的喜酒。\n");
     set("unit", "个");
     set("value", 20);
     set("no_sell",1);
     set("max_liquid",50);
   }

  
   set("liquid", ([
     "type": "alcohol",
     "name": "米酒",
     "remaining":35,
     "drunk_supply":30,
   ]));
}

