
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", GRN"花园"NOR);
	set("long", @LONG
这里是个花园。这里种了不少的鲜花，但还是有很多的竹子。旁边
还有已有一个石碑，上面写着：红豆一颗现真情，东溟茫茫无情愁。
LONG);
	set("exits", ([
	     
		"south" :__DIR__"shilu2",
		"north":__DIR__"shilu1",
		
		
	]));
	set("objects",([
		__DIR__"npc/shanxia":1,
	]));
     set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

