
 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("肘子", ({"zhou zi","zhou","zi"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是[醉花楼]的特色菜.\n");
                set("unit", "个");
                set("value", 540);
                set("food_remaining", 50);
                set("food_supply", 80);
        }
}

