
inherit ROOM;
#include <ansi.h>
void create()	
{
	set("short",HIY"边塞居"NOR);
	set("long", @LONG
这里是边塞居了。这里的男女主人是什么长生版(alongtwo)
和混天工(piin) 。两个人都以刚猛的武功而闻名江湖之中。 只
见这里摆着一张方桌，放着几个凳子，桌子上还有一壶刚刚沏好
的茶水。正面是两把太师椅，中间挂着一张观音菩萨像。北边是
一间卧室。
LONG);
    set("exits", ([
	        "east" : __DIR__"nandajie2",
	        "south":__DIR__"alongtwo_piin_woshi",
 	]));
      set("no_fight",1);
      setup();
      replace_program(ROOM);
	
}
