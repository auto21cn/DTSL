
#include <armor.h>
#include <ansi.h>
inherit HANDS;

void create()
{
   set_name(HIB"铁鹰爪手"NOR, ({ "tiezhua shou","shou"}) );
   set_weight(500);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "钢铁");
     set("long","这是一副武林人士常用的铁爪手。\n");
     set("unit", "副");
     set("value",2000);
     set("armor_prop/armor",20);
     set("armor_prop/damage",6);
   }
   setup();
}
