inherit ROOM;
#include <ansi.h>
string joke();
int do_search(string arg);
void create()
{
	set("short","书房");
	set("long", @LONG
这里是白老夫子的书房。两旁是书柜，上面放了很多书。正中央还
有一个大桌子，上面还有一幅没写完的字[zi]。
LONG);
        set("exits",([
          "out":__DIR__"tianjing",
          ]));
        set("objects",([
           __DIR__"npc/shilong":1,
           ]));
        set("item_desc",([
          "zi":(:joke:),
          ]));
        set("no_quit",1);
	setup();      
}
string joke()
{
  object ob;
  ob=this_player();
  return HIW+ob->name()+"是大唐双龙中最无耻、最没有前途的人！！\n\n"NOR+
                        "                                     白老夫子书\n";
}
void init()
{
  add_action("do_search","sou");
}
int do_search(string arg)
{
  object ob;
  object target,map;
  ob=this_player();
  if(!ob->query_temp("dtsl_quest_csj/step7"))
  return 0;
  if(!arg)
  return notify_fail("你要搜什么？\n");
  if(arg!="corpse")
  return 0;
  if(!objectp(target=present(arg,environment(ob))))
  return 0;
  if(target->query("dead_id")!="shi long")
  return 0;
  if(sizeof(children(__DIR__"obj/map"))>1)
  return 0;
  message_vision("$N蹲下身子在尸体上搜了一会，突然摸到一个羊皮卷！\n",ob);
  map=new(__DIR__"obj/map");
  map->move(ob);
  return 1;
}
