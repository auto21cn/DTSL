
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小路");
  set ("long", @LONG
这里是一条小路。这里已经是安徽的境地了。再往西走就可以到合
肥了。远处好象有哭喊的声音，不知是哪个百姓有被官兵、盗贼洗劫了。
LONG);

  set("exits", ([ 
 "eastdown":__DIR__"xiaolu1",
 "southwest":__DIR__"xiaolu3",
        ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

