inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
这里是通往西域的丝绸古路，繁华的城镇在身后慢慢消逝，迎面而
来的是阵阵风浪。不时有一队队商人丛你身边擦身而过。
LONG
        );
        set("exits", ([
          "southwest" : __DIR__"road3",
          "southeast" : __DIR__"road1",
        ]));

        set("outdoors", "tuyuhun");

        setup();
        replace_program(ROOM);
}
