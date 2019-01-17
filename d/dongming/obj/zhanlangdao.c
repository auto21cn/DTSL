
#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
   set_name(HIG"斩浪刀"NOR, ({ "zhan lang dao","dao","blade" }) );
   set_weight(4000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "柄");
	 set("super",6);
     set("value", 4000);
     set("material", "iron");
	 set("no_save",1);
     set("long", "这是一柄东溟派的宝刀，上面刻着[斩浪]二字。\n");
     set("wield_msg", "$N抽出一把明晃晃的$n握在手中。\n");
     set("unequip_msg", "$N将手中的$n插入腰间的刀鞘。\n");
   }
   init_blade(65,150,150);
   setup();
}
