
#include <weapon.h>
#include <ansi.h>
inherit WHIP;

void create()
{
	set_name(HIR"绝情鞭"NOR, ({ "jueqing bian","bian"}) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("no_save",1);
		set("long", "这是一个绝情鞭，透漏着深深的邪气。\n");
		set("value", 50);
		set("rumor",1);
		set("super",5);
		set("no_sell",1);
		set("material", "steel");
	}
	init_whip(170,180,180);


	set("wield_msg", "$N“啪”地一声抖了一下$n，握在手中。\n");
	set("unwield_msg", "$N将手中的$n盘在腰间。\n");


	setup();
}
