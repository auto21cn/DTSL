
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
   set_name(HIW"白衣"NOR, ({ "cloth"}) );
   set_weight(5000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "cloth");
     set("long","这是一件白纱衣，看起来淡雅脱俗。\n");
     set("unit", "件");
     set("value", 40);
     set("armor_prop/armor", 20);
   }
   setup();
}
