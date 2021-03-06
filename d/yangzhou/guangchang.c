
#include <ansi.h>
inherit ROOM;

int do_wa();
int do_pao();
int do_dig();
void create ()
{
  set ("short","瘦西湖");
  set ("long", @LONG
这里是扬州城的北湖堤了。这里是扬州景色最为秀丽的地方。这里
聚集了五湖四海的人们。扬州本就是交通的枢纽，再加上是烟花胜地，
所以江湖的豪客都要来这里逛逛，以显示自己的英雄本色。但是最近据
说宇文阀要来这里寻找武林绝迹[长生诀]，又弄的这里人心惶惶。
LONG);

  set("exits", ([ 
// "northeast":"/d/clone/room/paimai/paimaiwu",
 "east":__DIR__"guangchang1",
 "southwest":__DIR__"xihudi4",
 "northeast":__DIR__"beidajie1",
// "up":"u/kouzhong/chatroom",

        ]));
  set("objects",([
	  __DIR__"npc/yan":1,
	  __DIR__"npc/gongzi":1,
	  "/d/clone/npc/liguan":1,
	 // "/u/chris/xunbao/baiwutong":1,
	  ]));
  set("outdoors","yangzhou");
  
  set("valid_startroom", 1);
  setup();

}

int valide_leave(object ob,string dir)
{
  if(dir=="northeast"&&!userp(ob))
   return 0;
  
  return ::valid_leave(ob,dir);
}

void init()
{
  add_action("do_wa","wa",);
  add_action("do_pao","pao");
  add_action("do_dig","dig");
}
int do_wa()
{
  object ob;
  object thing;
  ob=this_player();
  if(ob->query("sen")<=0)
  return notify_fail("你精神疲惫，不能再挖了！\n");
  if(ob->is_busy())
  return notify_fail("你的动作没完成\n");
  ob->add("sen",-1);
  ob->start_busy(1);
  if(random(40)!=11){
  message_vision(CYN"$N张开五指，狠狠地向地里插去！\n"NOR,ob);
  return 1;}
  thing=new(__DIR__"obj/thing");
  thing->create_name();
  if(thing->query("name")=="铁钥匙"){
      if(random(100)>90)	
      thing->set_weight(100);
  }
  thing->move(environment(ob));
  message_vision(CYN"$N突然挖到一"+thing->query("unit")+thing->name()+"!\n"NOR,ob);
  return 1;
}
int do_pao()
{
  object ob;
  object thing;
  object weapon;
  ob=this_player();
  if(ob->query("sen")<=0)
  return notify_fail("你精神疲惫，不能再挖了！\n");
  if(!ob->query_temp("weapon"))
  return notify_fail("你想用手刨吗？\n");
  weapon=ob->query_temp("weapon");
  if(weapon->query("skill_type")!="staff")
  return notify_fail("你使用的武器不对！\n");
  if(ob->is_busy())
  return notify_fail("你的动作没完成\n");
  ob->add("sen",-1);
  ob->start_busy(1);
  if(random(40)!=11){
  message_vision(CYN"$N抡起"+weapon->name()+",朝地上狠狠刨去！\n"NOR,ob);
  return 1;}
  thing=new(__DIR__"obj/thing");
  thing->create_name();
  thing->move(environment(ob));
  message_vision(CYN"$N突然刨到一"+thing->query("unit")+thing->name()+"!\n"NOR,ob);
  return 1;
}
int do_dig()
{
  object ob;
  object thing;
  object weapon;
  ob=this_player();
  if(ob->query("sen")<=0)
  return notify_fail("你精神疲惫，不能再挖了！\n");
  if(!ob->query_temp("weapon"))
  return notify_fail("你想用手挖吗？\n");
  weapon=ob->query_temp("weapon");
  if(weapon->query("skill_type")!="sword"&&
     weapon->query("skill_type")!="blade"&&
     weapon->query("skill_type")!="dagger")
  return notify_fail("你使用的武器不对！\n");
  if(ob->is_busy())
  return notify_fail("你的动作没完成\n");
  ob->add("sen",-1);
  ob->start_busy(1);
  if(random(40)!=11){
  message_vision(CYN"$N抡起"+weapon->name()+",朝地上狠狠挖去！\n"NOR,ob);
  return 1;}
  thing=new(__DIR__"obj/thing");
  thing->create_name();
  thing->move(environment(ob));
  message_vision(CYN"$N突然挖到一"+thing->query("unit")+thing->name()+"!\n"NOR,ob);
  return 1;
}
