
#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
   set_name(HIR"彩衣"NOR, ({ "cai yi","cloth","yi"}) );
   set_weight(5000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "cloth");
	 set("long","这是一件五彩斑斓的衣服,妖娆如火.\n");
     set("unit", "件");
     set("value", 40);
     set("armor_prop/armor", 10);
   }
   setup();
}
