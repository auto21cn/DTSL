
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIB"铜殿"NOR);
  set ("long", @LONG
这里是净念禅院的铜殿。这做铜殿比其他大殿要小巧得多，但却似
乎比其他大上十倍的殿宇更有地位。这样一座阔深各达三丈，高达丈半
的铜殿，不但需极多的金铜，还要有真正的高手巧匠才成。
LONG);

  set("exits", ([ 
	  "east":__DIR__"shilu4",
	  "out":__DIR__"shilu3",
  
         ]));
  set("objects",([
	  __DIR__"npc/liaokong":1,
	  ]));

  
  set("valid_startroom", 1);
  setup();
 
}

