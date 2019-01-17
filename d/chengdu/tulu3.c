
inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
这是一条尘土飞扬的小路，因为四川自古就是富庶之地，所以放眼
望去，四周的田垅里郁郁青青。这里是川中，东北十几里处就是著名的
蜀都成都了。
LONG);
	

	set("exits", ([
        "north" : __DIR__"dananmen",
		"southwest" : __DIR__"tulu2",
	]));

	setup(); 
	replace_program(ROOM);
}
