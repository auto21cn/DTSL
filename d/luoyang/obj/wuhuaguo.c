
inherit ITEM;

void create()
{
        set_name("无花果", ({ "wuhua guo","guo" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
				set("long","这是一个无花果，它能用来炼制药物。\n");
                set("value", 200);
				set("heal",([
					"heals":20,
					]));
                
        }

      
        setup();
}
