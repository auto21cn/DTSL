
#include <ansi.h>
inherit ROOM;
void create ()
{
  set ("short",HIB"地下室"NOR);
  set ("long", @LONG
这里是一个地下室，四周黑漆漆的，看不出哪里有明显的出
口。
LONG);
 set("no_fight",1);
 set("valid_startroom", 1);
  setup();
 
}
void init()
{
	object ob;
	ob=previous_object();
	if(userp(ob))
	call_out("add_exit",300,ob);
	return;
   
}
void add_exit(object ob)
{
  tell_object(ob,YEL"你突然发现上面出现了一个出口！\n"NOR);
  tell_object(ob,"你纵身一跃，跳了上来！\n");
  ob->move(__DIR__"mishi");
  return;
}
