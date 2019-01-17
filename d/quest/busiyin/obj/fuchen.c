

#include <weapon.h>
#include <ansi.h>
inherit WHIP;

void create()
{
	set_name("拂尘", ({ "fu chen","fu","chen" }));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄拂尘。\n");	
		set("no_save",1);
		set("material", "steel");
		set("wield_msg", "$N抽出$n晃了几晃，握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回背后。\n");
	}
	init_whip(20,60,60);
	setup();
}
