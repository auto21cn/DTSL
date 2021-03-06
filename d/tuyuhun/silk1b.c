
inherit ROOM;

void create()
{
        set("short", "仙人崖");
        set("long", @LONG
这里以传说有神仙出没而得名，每到盛夏夜，火光从崖面飞出，名
曰仙人送灯。面山带水，群峰环峙，野草蒙茸，奇花异树，清幽险峻，
令人绝俗。
LONG);
        set("outdoors", "tuyuhun");

        set("exits", ([
                "northwest" : __DIR__"silk1a",
                "northeast" : __DIR__"silk",
        ]));
        set("objects",([
          __DIR__"npc/youke":1,
         ]));

        setup();
}

void init()
{
  add_action("do_linghui","linghui");

}

int do_linghui()
{
   object ob;
   string time,msg;
   
   ob=this_player();
   
   if(ob->query_skill("kuangsha-daofa",1)<160)
   return 0;
   if(ob->query("perform_quest/kuangsha"))
   return 0;
   if(ob->query_skill("feiwo-whip",1))
   return 0;
   
   time=NATURE_D->game_time();
   if(strsrch(time,"卯时三刻")==-1
     )
    return notify_fail("你现在什么也领会不出来。\n");
   
   msg="$N静静领会起狂沙刀法，对其中的“卷”字诀有了更深的认识！\n";
   message_vision(msg,ob);
   ob->set_temp("perform_quest/kuangsha_action1",1);
   if(ob->query_temp("perform_quest/kuangsha_action1")
    &&ob->query_temp("perform_quest/kuangsha_action2")
    &&ob->query_temp("perform_quest/kuangsha_action3")
    &&ob->query_temp("perform_quest/kuangsha_action4")
    &&ob->query_temp("perform_quest/kuangsha_action5")
     ){
    msg="$N微微一笑：狂沙刀法已然有所成就！\n";
    message_vision(msg,ob);
    ob->set("perform_quest/kuangsha",1);
    ob->delete_temp("perform_quest");
   }
   return 1;
}