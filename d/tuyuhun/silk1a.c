
inherit ROOM;

void create()
{
        set("short", "水帘洞");
        set("long", @LONG
这里群峰高耸，沿曲径入幽林，峰回路转，石壁中露出有拱形洞窟，
洞内水锈青苔，红绿班驳，乱石穿孔。雨季山顶飞流直下如水帘，因有此
名。
LONG);
        set("outdoors", "tuyuhun");

        set("exits", ([
                "southeast" : __DIR__"silk1b",
                "northeast" : __DIR__"silk1",
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
   if(strsrch(time,"寅时三刻")==-1
     )
    return notify_fail("你现在什么也领会不出来。\n");
   
   msg="$N静静领会起狂沙刀法，对其中的“滚”字诀有了更深的认识！\n";
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
