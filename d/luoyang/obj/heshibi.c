#include <ansi.h>
inherit ITEM;


void create()
{
   set_name(HIW"和氏璧"NOR, ({"heshi bi","bi"}));
   set_weight(700);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("long", "这就是天下人人想得到的和氏璧。\n");
     set("unit", "个");
     set("value", 20000000);
     
   }

}

