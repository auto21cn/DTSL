// /d/gaoli/yijiange.c
// Room in 弈剑小筑
// laowuwu 99/06/27
inherit ROOM;
void create()	
{
	set("short", "弈剑阁");
	set("long", @LONG
这是一代大侠傅采林的居所,也是弈剑派的核心,外派人员是进不来
的。这里布置的很简单，一张大床，几把椅子，窗前几朵剑梅，墙上挂
着一把宝剑。 东面是书房。
LONG
	);
set("exits", ([
		"south" : __DIR__"zhuangmen",
              
	]));
        set("objects", 
        ([ 
                __DIR__"npc/fucailin" : 1,
        ]));
       setup();
	replace_program(ROOM);
}	
