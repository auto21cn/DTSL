
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","马记裁缝店");
  set ("long", @LONG
这里是襄阳的一个裁缝店。这里的做的衣服美观大方，但是老板却
不顾形势，衣服的价格居高不下，所以几乎没有什么人来这里买衣服。
门口的桌子上放这一块布料，墙上贴着一张纸，上面写着：后天交货。
LONG);

  set("exits", ([ 
 "west":__DIR__"beidajie2",
        ]));
 set("objects",([
	 __DIR__"npc/ma":1,
	 ]));
 set("valid_startroom", 1);
  setup();
 
}

