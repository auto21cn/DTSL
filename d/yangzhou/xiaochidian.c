
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小吃店");
  set ("long", @LONG
这里是一家小吃店，这里的饭菜别具一格，吸引了各方的游客。什
么扬州蒸鸡、酱肘子等等，都是这里的名吃，也有很多江湖豪客专门来
这里吃扬州蒸鸡。这里的店小二跑来跑去，忙个不停。闻到菜香，你不
禁有些饿了。
LONG);

  set("exits", ([ 
 "north":__DIR__"xidajie2",
        ]));
  set("objects",([
	  __DIR__"npc/xiaoer3":1,
	  ]));
  set("valid_startroom", 1);
  setup();
 
}

