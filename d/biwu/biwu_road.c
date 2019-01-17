#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武走廊"NOR);
    set("long", @LONG
这是一个很短的走廊，侧门通向演武休息室，从大门进来直走，就是著名的
演武大厅。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("exits", ([
        "west"  : "/d/biwu/biwu_restroom",
        "south" : "/d/biwu/biwu_gate",
        "north" : "/d/biwu/biwu_dating",
    ]));

    set("no_clean_up", 0);
    set("coor/x", -60);
        set("coor/y", 10);
        set("coor/z", 0);
        setup();
}
 int valid_leave(object me, string dir)
{
        mapping conditions; 
        if (dir != "south") return 1;
//        if (wizardp(me)) return 1;

        if (mapp(conditions = me->query_condition()))
               me->clear_condition();
 
        if (me->query("eff_kee") < me->query("max_kee") ) 
               me->set("eff_kee",me->query("max_kee"));

        if (me->query("eff_gin") < me->query("max_gin"))
               me->set("eff_gin",me->query("max_gin"));

        return 1;
}

