// /d/gaoli/siheyuan
// Room in 山海关
// rich 99/04/05
inherit ROOM;
void create()	
{
	set("short", "四合院");
        set("long", @LONG
这里是塞漠帮的总坛，进进出出的都是塞漠帮的帮众，再往
北走就是就是塞漠帮的白虎堂，左右两间厢房是帮众住的地方。
LONG
	);
set("outdoors", "/d/shanhaiguan");
set("exits", ([
            	"west" : __DIR__"saimobang",
                "east" : __DIR__"baihutang",
                "north" : __DIR__"xiangfang1",
                "south" : __DIR__"xiangfang2",
	]));
       setup();
	replace_program(ROOM);
}
