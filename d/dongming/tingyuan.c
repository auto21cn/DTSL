
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", GRN"庭院"NOR);
	set("long", @LONG
这里是庭院。东面是东溟派弟子休息的地方。西面是个兵器库。这
里放着一个大铁炉，旁边有一个块牌子(pai)。
LONG);
	set("exits", ([
	     
		"south":__DIR__"chufang",
		"north":__DIR__"zhulin2",
		"east":__DIR__"sleep_room",
		"west":__DIR__"bingqiku",
		
	]));
set("objects",([
	__DIR__"npc/dizi2":1,
 "/d/clone/obj/tielu/tielu":1,
	]));
        set("item_desc",([
     "pai":"首先你要把炉子生起来，用点火[fire]\n"+
           "然后你要把冶炼的东西放到炉子中，[put],只可以放矿石，兵器。\n"+
           "然后你就要经常拉风箱[la 风箱],开始炼铁\n"+
           "如果不想炼了，可以开炉[kailu]取炼好的铁矿\n"+
           "炼铁的过程中，非常消耗内力可气血，要注意了\n",
           ]));
       set("valid_startroom", 1);   
       set("outdoors", "青石路");  
	setup();
       
       
}

int valid_leave(object me,string dir)
{
	if(dir=="west"&&
		me->query("family/family_name")!="东溟派"
		&&present("nan dizi",environment(me)))
	return notify_fail("男弟子拦住了你：非本派人物不得进入兵器库！\n");
	return ::valid_leave(me,dir);
}
