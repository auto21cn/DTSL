
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","半山腰");
  set ("long", @LONG
你走到了终南山的半山腰，你想继续向前欣赏路旁的没景，却突然
间发现没有路了，好不扫兴。你向四处望去，看见西面好象有一个凉亭，
使你不禁想走上前去休息一下。
LONG);

  set("exits", ([ 
"northdown":__DIR__"shandao2",
"west":__DIR__"liangting",
        ]));
 set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();

}

void init()
{
	add_action("do_jump","jump");
	
}

int do_jump(string arg)
{
   object ob;
   
   ob=this_player();
   
   if(!arg) return 0;
   if(arg!="ya"&&arg!="崖") return 0;
   
   message_vision("$N纵身朝山崖下跳去！\n",ob);
   
   ob->move("/d/clone/room/iron/room2");
   
   return 1;
   
}
