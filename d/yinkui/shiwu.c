
#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short",BLU"石屋"NOR);
  set ("long", @LONG
这里是一间石屋，里面非常阴暗，散发着阵阵潮湿的气息。屋子里
面有几个木头人，站位有置，似乎是某中阵法的排列。屋子的角落散落
着几个骷髅，黑洞洞的眼窝正对着你。
LONG);
  set("exits",([
	  "eastup":__DIR__"qingshilu2",
	  ]));
  set("objects",([
    __DIR__"npc/tmz_robot":4,
    ]));
  set("valid_startroom", 1);
  set("no_fight",1);
  setup();
 
}

void init()
{
   object ob;
   
   ob=this_player();
   
   if(!ob) return;
   if(ob->query("potential")<=0)
   return;
   if(!living(ob))
   return;
   
   remove_call_out("do_fight");
   call_out("do_fight",1,ob);
}

void do_fight(object ob)
{
    string msg;
    object *who;
    int i;
    
    if(!ob) return;
    
    if(environment(ob)!=this_object())
    return;
    if(ob->query("pker")){
      msg="\n只听天空一个响亮的声音朝$N说道：通缉犯，哪里逃！！\n\n";
      message_vision(msg,ob);
      ob->move(__DIR__"qingshilu2");
      ob->unconcious();
      return;
    }
    if(!ob->query_skill("tianmo-zhen",1)||
       !userp(ob)){
      msg="\n只见四个木人一齐朝$N撞来，$N连忙退了出去！\n\n";
      message_vision(msg,ob);
      ob->move(__DIR__"qingshilu2");
      return;
    }
    
    who=all_inventory(this_object());
    
    for(i=0;i<sizeof(who);i++){
      if(who[i]->query("tmz_robot"))
        who[i]->fight_ob(ob);
    }
   return;
}