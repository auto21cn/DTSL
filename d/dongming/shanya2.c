
inherit ROOM;
#include <ansi.h>
int do_tiao();
void create()
{
	set("short", GRN"山崖"NOR);
	set("long", @LONG
这里是山崖。从这里看去，远处海天一色，茫茫无边。向山崖下看
去，深不见底，不禁有些手脚发软了。
LONG);
	set("exits", ([
		"northeast":__DIR__"haitan3",
	        "southdown":"/d/job/dmjob/dmjob_0_13",
	]));
      set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

void init()
{
	add_action("do_tiao","tiao");
}

int do_tiao()
{
	object ob;
	ob=this_player();
	message_vision("$N纵身朝悬崖下面跳了下去！\n",ob);
	ob->receive_damage("sen",200);
	ob->move(__DIR__"yadi");
	return 1;
}
