
 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("米饭", ({"rice"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一碗米饭。\n");
                set("unit", "个");
                set("value", 100);
                set("food_remaining", 20);
                set("food_supply", 50);
        }
}

