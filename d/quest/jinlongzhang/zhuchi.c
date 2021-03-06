
inherit NPC;

string do_quest();

void create()
{
   set_name("清智禅师",({ "qing zhi","qing","zhi" }) );
        set("gender", "男性" );
        set("age", 60);
        set("class","bonze");
   set("long", "这是回龙寺的主持。\n");       
   set("combat_exp",500000);
   set("str",30);
   set("attitude", "peaceful");
  set_skill("dodge",171);
   set_skill("force",171);
   set_skill("parry",171);
   set_skill("finger",171);
   set_skill("dujie-zhi",171);
   set_skill("liuyun",171);
   set("force",1000);
   set("max_force",1000);
   set("max_kee",1500);
   set("max_gin",1500);
   set("max_sen",1500);
   set("inquiry",([
     "金龙禅杖":(:do_quest:),
     "禅杖":(:do_quest:),
     "staff":(:do_quest:),
     ]));
   setup();
   carry_object(__DIR__"jiasha")->wear();
  
}

string do_quest()
{
   object ob;
   object *t;
   
   ob=this_player();
   
   t=children(__DIR__"jinlong-zhang");
   if(sizeof(t)>=2)
   return "金龙禅杖已经送给别人了，你来晚了！\n";
   
   ob->set_temp("dtsl_lev1_quest_chanzhang/step1",1);
   return "好吧，如果你能战胜我，老衲就告诉金龙禅杖的地方！\n";
}

int end_fight(object killer,object victim)
{
  if(victim->query_temp("dtsl_lev1_quest_chanzhang/step1")){
   message_vision("$N呵呵一笑：你想拿这个宝物还差的远呢！\n",this_object());
   return 1;}
  return 1;
}

int surrender(object killer,object victim)
{
  if(killer->query_temp("dtsl_lev1_quest_chanzhang/step1")){
  message_vision("$N脸色一变：佩服佩服！好吧，宝物就在南边的厢房中，\n"+
                 "能不能拿到就看你的运气了！\n",this_object());
     killer->delete_temp("dtsl_lev1_quest_chanzhang/step1");
     killer->set_temp("dtsl_lev1_quest_chanzhang/step2",1);
     return 1;}
  return 1;
}