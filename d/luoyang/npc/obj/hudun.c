
#include <armor.h>
#include <ansi.h>
inherit SHIELD;

void create()
{
   set_name(HIB"护盾"NOR, ({ "hu dun","hu","dun","shield"}) );
   set_weight(1500);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "钢铁");
     set("long","这是一面护盾，正面雕着一些凶神模样的画像。\n");
     set("unit", "面");
     set("value",2000);
     set("armor_prop/armor",29);
     set("armor_prop/dodge",-1);
   }
   setup();
}
