
 
inherit ITEM;
inherit F_FOOD;

void create()
{
   set_name("烤羊腿", ({"kao yangtui","yangtui"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一个香气四溢的烤羊腿。\n");
                set("unit", "个");
                set("value", 100);
                set("food_remaining", 30);
                set("food_supply", 50);
        }
}

int is_get_of(object pal,object ob)
{
  if(pal->query("family/family_name")!="突厥")
  return notify_fail("只有突厥弟子可以捡这里的东西！！\n");
  return 1;
}