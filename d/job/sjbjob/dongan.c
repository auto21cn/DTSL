
inherit ROOM;
#include <job_money.h>
void create ()
{
  set ("short","长江北岸");
  set ("long", @LONG
这里扬州的南门外。北边就是扬州的北门了。南边是长江，滚滚的
江水从你脚下流过。西边是扬州的南门码头，从那里可以坐船渡过长江。
LONG);

  set("exits", ([ 
      "west":"/d/hangzhou/jiangbei",
//      "north":"/u/kouzhong/kuangchang",
"enter":"/d/quest/csj/ship",
      ]));
  set("valid_startroom", 1);
  set("outdoors","yangzhou"); 
  setup();
 
}

