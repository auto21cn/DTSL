
#include <weapon.h>

inherit WHIP;

void create()
{
        set_name("拂尘", ({"fu chen", "fu","chen"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把道士常用的拂尘．\n");
                set("value", 100);
                set("material", "iron");
                set("wield_msg","$N拿出一把$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_whip(25,100,100);
        setup();
}

