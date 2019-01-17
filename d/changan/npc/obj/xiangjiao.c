
 
inherit ITEM;
inherit F_FOOD;
int do_eat(string arg);
void create()
{
   set_name("香蕉", ({"banana"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一个香蕉，很好吃的。\n");
                set("unit", "个");
                set("value", 600);
                set("food_supply", 30);
		call_out("rid",120,this_object());
        }
}

void init()
{
	add_action("do_eat","eat");
}
int do_eat(string arg)
{
	int food_s;
	object me,ob;object pi;
    me=this_player();ob=this_object();
	if(!arg||arg!="banana")
		return notify_fail("你要吃什么？\n");
	if( (int)this_player()->query("food") >= (int)this_player()->max_food_capacity() )
     return notify_fail("你已经吃太饱了，再也塞不下任何东西了。\n");
    food_s=ob->query("food_supply");
	ob->add("food_supply",-5);
	me->add("food",10);
	message_vision("$N拿起"+ob->name()+"吃了几口\n",me);
	if(ob->query("food_supply")<=0)
	{
		//pi=new(__DIR__"pi");
		//pi->move(environment(me));
		destruct(ob);
		return 1;
	}
	return 1;
}

void rid(object ob)
{
	destruct(ob);
	remove_call_out("rid");
	return;
}