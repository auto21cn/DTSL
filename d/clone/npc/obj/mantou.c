
inherit ITEM; 
inherit F_FOOD;

void create()
{
   set_name("馒头", ({"mantou"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一个白馒头。\n");
                set("unit", "个");
                set("value",1);
                set("food_remaining", 20);
                set("food_supply", 10);
        }
}

