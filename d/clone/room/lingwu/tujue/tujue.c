
#include <ansi.h>
inherit ROOM;
int do_lingwu(string arg);
void create ()
{
  set ("short",HIB"密室"NOR);
  set ("long", @LONG
这里是一个密室，四周黑暗，只有一支蜡烛放在面前的桌子
上。旁边有几个软蒲团，正面还挂着一幅对联，上面的字迹已经
模糊不清。你可以在这里领悟lingwu突厥的内功心法----炎阳大
法。
LONG);

  set("exits", ([ 
 "out":"/d/dingxiang/guoshifu",
        ]));
  set("no_channel","领悟中还是不要说话了\n");
  set("no_tell","领悟中还是不要说话了\n");
  set("valid_startroom", 1);
  set("force","yanyang-dafa");
  setup();
 
}
void init()
{
   add_action("do_lingwu","lingwu");
}
#include "/d/clone/room/lingwu/lingwu.c"
