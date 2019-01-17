
#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","小船");
  set ("long", @LONG
这里是一艘小船，里面布置的非常华丽。里面还有一个套间，门紧
关着，不知道里面的人在做什么。这里放着一张大桌子，上面摆放着一
些酒菜。
LONG);

  set("exits", ([ 
  
  "up":__DIR__"baihuqiao",
  
         ]));
   
  set("valid_startroom", 1);
  setup();
 
}

void init()
{
   add_action("do_touting","touting");
   add_action("do_steal","search");

}

int do_touting()
{
   object ob;
   string msg;
   
   ob=this_player();
   
   if(ob->query("family/family_name")!="花间派")
   return 0;
   if(ob->query("execute_quest/busiyin"))
   return 0;
   if(!ob->query_temp("steal_busiyin/action0"))
   return 0;
   if(ob->query_temp("steal_busiyin/action2"))
   return 0;
   if(present("steal_busiyin_obj",ob))
   return 0;
   
   msg="$N偷耳朝里面的房间听去，只听一男一女在轻声说话，态度非常暧昧。\n";
   message_vision(msg,ob);
   ob->set_temp("steal_busiyin/action1",1);
   ob->delete_temp("steal_busiyin/action0");
   return 1;
}

int do_steal()
{
   object ob,book;
   string msg;
   
   ob=this_player();
   
   if(ob->query("family/family_name")!="花间派")
   return 0;
   if(ob->query("execute_quest/busiyin"))
   return 0;
   if(!ob->query_temp("steal_busiyin/action1"))
   return 0;
   
   ob->delete_temp("steal_busiyin/action1");
   ob->set_temp("steal_busiyin/action2",1);
   
   msg="$N轻手轻脚翻了翻地上的衣服，忽然发现一本书！\n";
   message_vision(msg,ob);
   book=new(__DIR__"obj/book");
   book->move(ob);
   call_out("do_hit",5,ob);
   return 1;
}

void do_hit(object ob)
{
  if(!ob) return;
  if(environment(ob)!=this_object())
  return;
  
  message_vision("\n突然杨虚彦从里面出来，朝$N喝道：你敢在我眼皮下偷东西！\n"+
                 "杨虚彦钢剑出手，$N一个不防备，正中眉心！\n\n",
                 ob);
  ob->unconcious();
  return;
}