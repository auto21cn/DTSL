
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","凉亭");
  set ("long", @LONG
这里是一座凉亭，清风吹来，顿时让人神清目爽。东边是一个长廊，
不时有阴癸派的弟子从那里走来。凉亭上摆着几盆鲜花，个个色彩艳丽，
妖娆无比。
LONG);
  set("exits",([
	  "east":__DIR__"changlang",
	  "southwest":__DIR__"zhulin",
	  ]));

  set("outdoors","yinkui");

  set("valid_startroom", 1);
  setup();
 
}

