
 
inherit ITEM;
inherit F_FOOD;
#include <ansi.h>
void create()
{
   set_name(HIY"元月蒸鸡"NOR, ({"zheng ji","ji"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是元月蒸鸡，看起来非常好吃。\n");
                set("unit", "盘");
                set("no_sell",1);
                set("value", 60);
                set("no_decay",1);
                set("food_remaining",200);
                set("food_supply",200);
        }
}

