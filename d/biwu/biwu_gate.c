#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武大门"NOR);
    set("long", @LONG
这是一个金色的门廊，往北是一个宽阔的走廊，尽头就是比武大厅。大唐的
顶级高手通过擂台比武一争高低，比武大厅是大唐所有武者心中的圣地。如果能
够跻身十大高手金榜，更是无上荣誉，风光至极。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "north" : "/d/biwu/biwu_road",
        "down" : "/u/kouzhong/chatroom",
    ]));

    set("no_clean_up", 0);
    set("coor/x", -60);
        set("coor/y", 0);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        mapping conditions;
        object *inv;
 
        if (dir != "north") return 1;

        if (mapp(conditions = me->query_condition()))
               return notify_fail("对不起，你的身体状况不好，不能进入！\n");

        if (me->query("eff_kee") < me->query("max_kee") ) 
               return notify_fail("对不起，你的气血受伤了，不能进入！\n");

        if (me->query("eff_gin") < me->query("max_gin"))
               return notify_fail("对不起，你的精气受伤了，不能进入！\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                tell_object(me, "你背的是谁？还不快快放下！\n");
                return 0;
        }

        inv = 0;
        return 1;
}


