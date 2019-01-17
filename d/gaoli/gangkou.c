// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
#include <ansi.h>
#define SHIPDIR "/d/job/sjbjob/ship"
#define FROM __DIR__"gangkou"
#define TO "/d/job/sjbjob/gangkou"
#include "/std/shiproom.c";
void create()	
{
	set("short", "港口");
	set("long", @LONG
这里是一个港口，这里非常热闹，停泊着各种船只，有货船，商船
等等。很多旅客从这里进出港口，有从中原来的，也有从其他地方来的。
许多小贩在这里叫卖。这里有一个牌子(pai)。
LONG
	);
set("outdoors", "/d/gaoli");
set("exits", ([
		"north" : __DIR__"dadi6",
   "east":"/d/job/killhaidao/gangkou",
        	//"south":__DIR__"gangkou",
	]));
	set("item_desc",([
  "pai":"每次船费纹银十两，银票不收。\n",
  ]));
  	set("no_duhe",1);
       setup();
	
}

int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","gangkou");
  if(dir=="enter"){
  switch(MONEY_D->player_pay(ob,1000)){
  	case 0:return notify_fail("水手说道：你的船钱不够啊!\n");
  	case 2:return notify_fail("水手说道：银票我们找不开的！\n");
  	default:break;}
   return ::valid_leave(ob,dir);}
  return ::valid_leave(ob,dir);
}

