
inherit ROOM;
 void create()
{
       set("short", "沙石路");
       set("long", @LONG
这里是条沙石路。南边是一片热带雨林，据说里面有很多毒蛇猛兽。
你不由得小心起来。
LONG);
       set("exits", ([
               "northeast" : __DIR__"shalu1",
               "southwest" : __DIR__"shulin1",
                    ]));

       setup(); 
       replace_program(ROOM);
}


