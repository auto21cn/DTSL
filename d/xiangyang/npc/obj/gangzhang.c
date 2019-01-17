
#include <weapon.h>
//#include <ansi.h>
inherit STAFF;

void create()
{
	set_name("钢杖", ({ "gang zhang","zhang","staff" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long","这是一把普通的钢杖。\n");
		set("value",600);
		set("material", "steel");
	}
	init_staff(20,150,150);

	set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
	set("unwield_msg", "$N将手中的$n放到地上。\n");

	setup();
}
