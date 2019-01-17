#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "大榕树上");
        set("long", @LONG
人说大树底下好乘凉，没想到大树上更凉快。这棵大榕树真不愧为千年神木，
至今仍绿叶繁茂。据说这里的时间是冻结的，因此便成为许多玩家聊天的地方。
这里摆着几张用榕树根做的椅子，中间用几根榕树枝搭在一起，算是一个茶几了。
当你抬头往上看的时候似乎有个影在树梢之间移动，不过也许是风吹动所造成的
错觉。

LONG
        );
set("no_time", 1);
set("chat_room",1);
        set("freeze",1);
        set("no_clean_up", 0);
        set("exits", ([
        "down": "/d/yangzhou/guangchang",
        ]));
        set("objects", ([
       "/u/kouzhong/shizhe" : 1,
]));
         set("no_fight",1);
         set("no_magic",1);
         set("no_time",1);
          set("valid_startroom","1");
        set("freeze",1);
        setup();
        call_other("/obj/board/comm_b", "???");
}
void init()
{
    add_action("do_jump","tiao");
add_action("discmds",({"sleep","respitate","exert","array","duanlian","ansuan","touxi","persuade","teach","exert","exercise","study","xi","learn","kill","steal","xue","conjure","fight","hit","xi","perform","prcatice","scribe","tuna","surrender"}));
    add_action("do_climb", "climb");
}
int no_action(string str)
{
       write(HIY"树上别乱来！！！ \n"NOR);
       return 1;
}
int discmds()
{
        tell_object(this_player(),"现在你还是专心聊天吧！\n");
        return 1;
}



int do_jump(string arg)
{
        object me;
        me = this_player();
        if( !arg || arg!="down") return notify_fail("你要往哪跳？\n");
      if (me->is_fighting() || me->is_busy() )  return notify_fail("你正忙着呢！\n");
        message("vision",
                me->name() + "犹豫了一下，鼓起勇气，跳了下去。\n“嘭”的一巨响，似乎听到"+me->name()+"惨嚎了一声!\n",
                environment(me), ({me}) );
                me->move("/d/yangzhou/guangchang");
        message("vision",
                me->name() + "惨嚎一声，从树上掉了下来。\n",
                environment(me), ({me}) );
        return 1;
}
int valid_leave(object me, string dir)
{

        if ( dir=="down" && !wizardp(me))
        return notify_fail("盘根不知道给哪个坏家伙砍断了猓蠢粗荒跳爬(tiao)下去！\n");
         if ( dir=="up" && !wizardp(me))
        return notify_fail("这里没法直接走，看来你只能爬(climb)上去！\n");

        else return 1;
}



