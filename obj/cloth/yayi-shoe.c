// seng-xie.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( WHT "薄底快靴" NOR, ({ "xue", "shoe" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
		set("long", "一双衙役的官鞋。\n");
		set("value", 0);
		set("material", "boots");
		set("armor_prop/dodge", 5);
              set("no_give", "随身的东西不能给人。\n");
	}
	setup();
}
