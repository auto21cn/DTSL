

#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "大北门");
	set("long", @LONG
这是就是成都的北城门了。成都地处川中，地势险要，所以战事较
少。有几个官兵正在检查来往的百姓。
LONG);


	set("exits", ([
		"south" : __DIR__"beidajie4",
		"northeast":"/d/luoyang/guanlu4",
	]));
	set("object",([
		__DIR__"npc/bing":2,
		]));
        set("outdoors", "成都");
	setup();
}


