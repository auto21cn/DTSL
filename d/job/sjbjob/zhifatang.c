
#include <ansi.h>
#include <job_money.h>
inherit ROOM;

string give_job();
int do_ok(string arg);

string *dir1=({
"/d/wuyishan"
});

string *dir2=({
"/d/taishan","/d/huashan"
});

string *dir3=({
"/d/emeishan","/d/suiye","/d/dingxiang"
});

void create ()
{
  set ("short",HIR"执法堂"NOR);
  set ("long", @LONG
这里是宋家堡的执法堂。宋家堡的弟子犯了错误，都要到这里来接
受处罚。不过有些弟子已经成了宋家堡的叛徒，早已逃到其他地方。宋
家堡一直在抓拿这些叛徒。所有叛徒的名字都写在挂在墙上的这张大榜
(bang)上。
LONG);

  set("exits", ([ 

   "north":"/d/lingnan/modaotang",
       ]));
  set("item_desc",([
	  "bang":(:give_job:),
    ]));

  set("valid_startroom", 1);
 
  setup();
 
}

void init()
{
  add_action("do_ok","task");
}

string give_job()
{
  object ob,killer;
  string *dirs,str;
  
  ob=this_player();
  
  if(ob->query("combat_exp")<100000)
  return "江湖小混混一边呆着去！\n";
  
  if(ob->query_temp("song_kill_pantu_msg"))
  return ob->query_temp("song_kill_pantu_msg");
  if(time()-ob->query("busy_time")<40+random(5))
  return "你看了看，发现上面还没有叛徒的名单出现。\n";
  if(ob->query_temp("dtsl_job"))
   return "你正在做其他任务，先忙其他的吧！\n";
   if(!valid_do_job(ob,"song"))
	return "你的武功很高了，做这样的小事真是大才小用了！\n";
  
  if(ob->query("combat_exp")<500000)
    dirs=dir1;
  else
  if(ob->query("combat_exp")<900000)
    dirs=dir1+dir2;
  else
    dirs=dir1+dir2+dir3;
    
  killer=new(__DIR__"killer");
  
  if(!killer->set_status(ob))
   return "叛徒出问题了，快去报告巫师！\n";
  
  if(!random_place(killer,dirs))
   return "上面的字迹有些模糊不清。\n";
  
  if(!environment(killer))
   return "上面的字迹有些模糊不清。\n";
  	
   ob->set_temp("dtsl_job","宋家堡杀叛徒任务");  
   ob->set_temp("song_kill_pantu",1);
  str=
  "             "+HBMAG+"宋家堡叛徒榜"+NOR+"\n"+ 
  YEL"**************************************\n"NOR+
  "\n\n      "+MISC_D->find_place(environment(killer))+"\n"+
  "\n      "+killer->name()+"\n\n\n"+
  YEL"**************************************\n\n\n\n"NOR;
  ob->set_temp("song_kill_pantu_msg",str);
  ob->add_temp_array("job_temp_killer",killer);
  return str;
}

int do_ok(string arg)
{
  object ob;
  
  ob=this_player();
  if(!arg||arg!="ok")
  return notify_fail("什么？\n");
  if(!ob->query_temp("song_kill_pantu"))
  return notify_fail("什么？\n");
  if(!ob->query_temp("song_kill_pantu_ok"))
  return notify_fail("没有杀死叛徒，怎么就回来交差了？\n");
  ob->delete_temp("song_kill_pantu");
  ob->delete_temp("song_kill_pantu_ok");
  ob->delete_temp("song_kill_pantu_msg");
  ob->delete_temp("dtsl_job");
  ob->set("busy_time",time());
  
  JOBSYS_D->give_reward_sjbkillpantu(ob);
  
 return 1;
}
