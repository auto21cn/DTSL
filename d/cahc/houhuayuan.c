
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","后花园");
  set ("long", @LONG
你缓步向后山走去。那山也不甚高，身周树木葱翠，四下里轻烟薄
雾，出没于枝叶之间。你足踏软草，竟连脚步也是悄无声息。将到山顶，
转了两个弯，一阵清风，四周全是花香。放眼望去，漫坡尽是红色、白
色、黄色的玫瑰。
LONG);

  set("exits", ([ 
 "northwest":__DIR__"tianjing",
 "south":__DIR__"huiketing",
 "northeast":__DIR__"lianwuting",
 "east":__DIR__"jiashan",
        ]));
  
  set("outdoors","changan");
  
  set("valid_startroom", 1);
  setup();
 
}

