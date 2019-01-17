//牢房大门laogate.c
inherit ROOM;
void create()
{
set("short","牢房大门");
set("long",@LONG
一扇沉重的大门豁然出现在你面前。这里就是关押犯人的牢房所在。门
口有两个看守，半倚在墙上，腰间挂着明晃晃的钢刀。他们一看你进来，立
刻直起身子，警惕着你。大门(men)看起来非常结实，想打破(break)它还真
不容易。
LONG);
set("exits",([
"east":__DIR__"showroom",
]));
set("objects",([
__DIR__"npc/kanshou":2,
]));
setup();
}
void init()
{
add_action("do_break","break");
}
int do_break(string arg)
{
object me;
me=this_player();
if(!arg||arg=="") return 0;
if(arg!="men")
return notify_fail("你想震什么？\n");
if(present("kan shou",this_object()))
{
write("你刚摆出姿势，只听看守大喝一声：“你想干什么？”\n");
message_vision("$N想震碎大门，但被看守阻止了。\n",me);
return 1;
}
else
{
write("你大喝一声，向大门劈去一掌。\n");
message_vision("$N震碎了大门。\n",me);
set("exits/south", __DIR__"laofang");
return 1;
}
}
