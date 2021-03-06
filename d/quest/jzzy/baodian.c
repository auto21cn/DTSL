
inherit ROOM;

void create()
{
	set("short", "罗汉堂");
	set("long", @LONG
这里塑像罗列，分作两组，中央是数十尊佛和菩萨，以居於殿心的
千手观音最为瞩目，不但宝相庄严，且因每只手的形状和所持法器无有
相同，令人生出神通广大，法力无边的感觉。五百罗汉分列四周，朝向
中央的塑像，形成纵横相通的巷道。
LONG);
        set("outdoors", "成都");

	set("exits", ([
		"out":"/d/chengdu/dadian",
	]));
	set("objects",([
	  __DIR__"obj/luohan":1,
	  ]));
        
        set("killer_reward",1);
	setup();
	
}

void killer_reward(object killer,object victim)
{
  if(!killer||!victim)
  return;
  if(!userp(killer)||!userp(victim))
  return;
  if(!killer->query_temp("dtsl_quest_jzzy_action1"))
  return;
  if(victim->query("combat_exp")<=killer->query("combat_exp"))
  return;
  if(victim->query("vocation")!="杀手")
  return;
  
  tell_object(killer,"你站在罗汉座前，有若陷身由塑像布下的迷阵中，\n"+
  "那感觉实非任何言语可以形容万一。\n");
  
  killer->delete_temp("dtsl_quest_jzzy_action1");
  killer->set_temp("dtsl_quest_jzzy_action2",1);
  
  return;
}