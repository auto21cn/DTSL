
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","�Թ�");
  set ("long", @LONG
������һ���Թ�����·���۸��ӣ����ҹ��߲��㣬�ǳ�������·��
������һЩ�к�ʬ�ǣ��������������Թ��е������µġ�
LONG);

  set("exits", ([ 
 "east":__DIR__"migong1",
 "west":__DIR__"migong2",
 "south":__DIR__"migong3",
 "north":__DIR__"migong7",
        ]));  
  set("valid_startroom", 1);
  setup();
 
}
