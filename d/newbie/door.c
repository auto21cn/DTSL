
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","大唐学院");
  set ("long", @LONG
欢迎来到网络游戏大唐双龙！在这里你将体验一个与众不同的生活！
这里是大唐双龙传的学院，可以教你学会在大唐双龙中生活的基本知识。
当然这里不会让你学会所有的东西，许多东西你需要使用 help 命令查看。
如 help 或 help 标题。对于游戏更新，请使用 news 命令来查看。如果
你觉得没有必要在这里学习东西，可以使用down来开始大唐的生活。如果
你想具体看看学院的内容，请 enter 进入学院来学习吧！对于一切新人，
可以到石龙武馆的礼官那里用 ask li about 大唐双龙 来要礼物。
LONG);

  set("exits", ([ 
 "down":"/d/slwg/zoulang1",
 "enter":__DIR__"room1",
        ]));
  
set("no_fight",1);
set("no_exert",1);
  set("valid_startroom", 1);
  setup();
 
}

