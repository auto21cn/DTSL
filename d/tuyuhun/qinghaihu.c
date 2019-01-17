
inherit ROOM;

void create()
{
        set("short", "青海湖");
        set("long", @LONG
眼前是一片大湖，这片湖水养育了居住在沙漠中的人们，所以被人
们尊敬的称为“圣湖”，湖中心有个小岛，上面落满了成千上万的各种
鸟，有的盘旋飞舞，有的静卧休憩，忽然起了一阵骚动，于是千万只鸟
竞相飞向蓝天，形成了一片壮观的图画。
LONG );
        set("outdoors", "tuyuhun");
        set("exits", ([
                "southeast" : __DIR__"shatulu1",
                "west" : __DIR__"shamo1",
                "northwest" : __DIR__"shamo2",
        ]));
        set("objects",([
          __DIR__"npc/daoke":1,
         ]));
         
        set("valid_startroom", 1);
        setup();
}

