// /d/gaoli/ zhuangmen
// Room in  庄门
// laowuwu 99/06/27
inherit ROOM;
void create()	
{
	set("short", "弈剑小筑");
	set("long", @LONG
你来到了弈剑派的门外,两扇漆黑的大门敞开着,高丽正德王
所亲提的大字"弈剑小筑"，这里就是傅采林隐居的弈剑小筑了。
LONG);
set("outdoors", "/d/yijiange");
set("exits", ([
		"north" : __DIR__"yijiange",
                "southeast" :__DIR__"xiaojing",
                
              
	]));
        set("objects", 
        ([
                __DIR__"npc/qiang" : 1,
        ]));
       setup();
	replace_program(ROOM);
}	
