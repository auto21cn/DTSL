
#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
	set_name(HIB"铜萧"NOR, ({ "tong xiao","xiao"}) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("no_save",1);
		set("long", "这是一把铜萧，上面画着一些古怪的图案。\n");
		set("value", 50);
		set("rumor",1);
		set("super",5);
		set("no_sell",1);
		set("material", "steel");
	}
	init_sword(170,180,180);


	set("wield_msg", "$N潇洒地抽出$n握在手中。\n");
	set("unwield_msg", "$N将手中的$n藏入怀中。\n");


	setup();
}
