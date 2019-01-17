// /d/gaoli/guangchang
// Room in 山海关
// rich 99/04/05
inherit ROOM;
void create()	
{
	set("short", "中央广场");
	set("long", @LONG
这里是山海关的正中心，一个很宽阔的广场，铺着青石地面。一条
南北大道把广场一分为二，东边冷冷清清见不到几个行人，西面人声鼎
沸，一派繁华景象。西北一条石板路不知通向何处。
LONG
	);
set("outdoors", "/d/shanhaiguan");
set("exits", ([
	        "north" : __DIR__"beidajie",
            	"south" : __DIR__"nandajie",
                "east" : __DIR__"dongdajie",
                "west" : __DIR__"yamendamen",
                "northwest" : __DIR__"shibanlu",
	]));
 set("objects", ([
		"/d/shanhaiguan/npc/boy" : 1,
		//"/d/job/songwupin/rong" : 1,
	]));
 
       setup();
	replace_program(ROOM);
}
