
inherit ITEM;

#include <ansi.h>

void create()
{
   set_name("《岳山手卷》", ({ "yueshan shoujuan","book","shoujuan"}));
   set_weight(100);
   set("unit", "本");
   set("long","这是一本岳山留下的武学手卷。\n");
   set("no_give",1);
   
}

string long()
{
   string msg;
   
   if(query("no_use"))
   return query("long");
   
   msg="$N看着"+query("name")+"记载的武学秘籍，似乎从中领悟到了一些东西！\n";
   message_vision(msg,this_player());
   this_player()->set_temp("dtsl_quest_jzzy_action1",1);
   set("no_use",1);
   return query("long");
}