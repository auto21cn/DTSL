// /d/gaoli/yamendating
// Room in 山海关
// rich 99/04/05
inherit ROOM;
void create()	
{
	set("short", "衙门大厅");
        set("long", @LONG
堂上东西有两根楹住，挂着一幅对联，但是你无心细看。正墙上悬
挂一个横匾，上书“正大光明”四个金光闪闪的大字。知府正坐在文案
后批阅文书，师爷随侍在后。
LONG
	);
set("exits", ([
            	"east" : __DIR__"yamendamen",
                "enter":"/d/clone/room/cityroom/shanhaiguan",
	]));
       setup();
	replace_program(ROOM);
}
