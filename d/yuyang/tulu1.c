

inherit ROOM;


void create()
{
	set("short", "小土路");
	set("long", @LONG
这是一条尘土飞扬的小路，不过在以前这里是连接山海关和渔阳的
唯一路径。现在由于已经修建其它的道路，自然走的人也就少了。
LONG);
	
	set("exits", ([
		"north" : __DIR__"tulu2",
                "southwest" : __DIR__"eroad",
	]));
    
	set("outdoors", "qiuci");
	setup();
	replace_program(ROOM);
}
