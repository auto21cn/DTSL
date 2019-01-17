
#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
	set_name(HIY"弯月刀"NOR, ({ "wanyue dao","dao","blade"}) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("no_save",1);
		set("long", "这是一把弯月刀，上面闪着金色的光芒。\n");
		set("value", 50);
		set("rumor",1);
		set("super",5);
		set("no_sell",1);
		set("material", "steel");
	}
	init_blade(170,180,180);


	set("wield_msg", "$N潇洒地抽出$n握在手中。\n");
	set("unwield_msg", "$N将手中的$n插入刀鞘。\n");
	setup();
}
