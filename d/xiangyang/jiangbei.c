
#include <ansi.h>

inherit ROOM;

#define SHIPDIR __DIR__"ship"
#define FROM __DIR__"jiangbei"
#define TO __DIR__"jiangnan"
#include "/std/shiproom.c";
#include <job_money.h>

void create ()
{
  set ("short","长江北岸");
  set ("long", @LONG
这里是长江的北岸。过了长江，就到了湖南的境地了。眼前江水滚
滚，只有一叶扁舟摆渡来往的行人。
LONG);

  set("exits", ([ 

  "north":__DIR__"xiaolu2",
         ]));

  set("valid_startroom", 1);
  set("outdoors","jiang");
  setup();
 
}

