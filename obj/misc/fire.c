inherit ITEM;
void create()
{
	set_name("火把", ({ "fire stick","fire" }));
       	set("long", "这是一根普通的火把。\n");
	set("weight", 30);
	set("unit", "根");
	set("value", 5);
	set("material", "木");
	setup();
}	
void init()
{
	add_action("fire","fire");
}
int fire()
{
	object me=this_player();
	me->set_temp("light",time());
	message_vision("$N将火把点燃。\n",me);
	set("long","燃烧着的火把。\n");
	set("value", 0);
	call_out("delay", 300, 1);
	return 1;
}
void delay(int phase)
{
	switch(phase) {
	case 1:
		write("火把已经烧掉一半了。\n" );
		set("long","烧掉一半的火把。\n");
		call_out("delay", 240, phase + 1);
		break;
	case 2:
		write("火把已经烧完大半截了，再烧下去就要烧到你的手了。\n" );
		set("long", "快烧完了的火把。\n");
		call_out("delay", 60, phase + 1);
		break;
	case 3:
		write("不经意中，火把就要烧到你的手了，你立即扔掉了手中的火把。\n" );
		message_vision("$N将烧过的火把扔到地上。\n",this_player());
		this_player()->delete_temp("light");
		destruct(this_object());
		break;
	}
}
