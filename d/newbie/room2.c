
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","战斗篇");
  set ("long", @LONG
这里是学院中教你学会战斗的地方。对于一个刚刚来到大唐的人来
说，最好先看看 help combat。这里的战斗方式可能你从来没有见过的。
如果你和对方没有什么仇恨，最好使用 fight命令来切磋武艺。如果你
和对方真的有仇恨，可以使用 kill 命令来杀死对方。当然，如果卑鄙
一些，可以使用 ansuan 命令来暗算对方，如果你投身杀手职业，可以
使用 ansha 命令来暗杀对方。这些命令都可以使用 help来查看。对于
战斗中的其他心得，还是请教一些江湖豪客吧！
LONG);

  set("exits", ([ 
 "west":__DIR__"room1",
        ]));
  
set("no_fight",1);
set("no_exert",1);
  set("valid_startroom", 1);
  setup();
 
}

