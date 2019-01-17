#include <room.h>

inherit ROOM;
void create()
{
	set("short", "岸边");
	set("long", @LONG
这是河边的块开阔地。河上架着几座浮桥，向西一条大道穿过树林
不知道通向那里。
LONG );
	set("exits", ([
		"eastup"     : __DIR__"shanlu3",
		"west"     : __DIR__"fuqiao",
	]));
	set("outdoors", "pingliang");
	setup();
	replace_program(ROOM);
}

