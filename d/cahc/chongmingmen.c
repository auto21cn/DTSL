
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","重明门");
  set ("long", @LONG
这里是东宫的南大门，隋文帝时，太子杨勇在此居住，后来被杨广
发动政变所杀，李阀攻陷长安后，东宫就成了太子李建成的住所。有不
少带刀侍卫认真的把守在门前。
LONG);

  set("exits", ([ 
 "north":__DIR__"xiandemen",
 "south":__DIR__"hggc3",
        ]));
  set("objects",([
          "/d/changan/npc/shiwei":2,
        ]));
  set("outdoors","changan");
  set("valid_startroom", 1);
  setup();
 
}

