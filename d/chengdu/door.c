
inherit ROOM;
 void create()
{
       set("short", "李财主家");
       set("long", @LONG
这里是李财主家。李财主是成都的一大富户。他的女儿长得更是千
娇百媚。每天登门求亲的人都络绎不绝。据说李财主和成都的独尊堡关
系密，所以李财主在成都也是占据一席之地。
LONG);
       set("outdoors", "成都");

       set("exits", ([
               "north" : __DIR__"dongdajie2",
			   "enter":__DIR__"tingyuan",
                         
       ]));
	   set("objects",([
		   __DIR__"npc/jiading":1,
		   ]));

       setup(); 
      
}

int valid_leave(object me,string dir)
{
	if(objectp(present("jia ding",environment(me)))&&dir=="enter")
		return notify_fail("家丁伸手一拦:里面你可不能进去!\n");
	return ::valid_leave(me,dir);
}

