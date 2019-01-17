
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIR"阴癸山门"NOR);
  set ("long", @LONG
这里就是「阴癸派」的山门了。作为江湖第一大邪教，这里的看守
可谓严格。这里地点隐蔽，平常人等是很难找到的。过了这里，就是阴
癸派的内部了。据说阴癸派的武功以邪恶著称，学成之后每个都是凶狠
残忍，所以平时没有人敢来这里的。
LONG);

  set("exits",([
      "north":__DIR__"xiaoshilu1",
      "eastdown":"/d/chengdu/shijie6",
	  "east":__DIR__"caocong1",
	  ]));
  set("objects",([
	  __DIR__"npc/dizi2":1,
	  ]));
  set("outdoors","luoyang");
  set("valid_startroom", 1);
  setup();
   "/obj/board/party_yg_b.c"->foo();
 
}

