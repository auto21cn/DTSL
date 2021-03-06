
inherit NPC;
#include <ansi.h>
string give_msg();
string do_quest();
string do_jzzy_quest();

int do_action1();
int do_action2();
int do_action3();
int do_action4();
int do_action5();
int do_action6();
int do_action7();

void create()
{
       int i;
       object *ob;
       set_name("石青璇", ({ "shi qingxuan","shi","qingxuan","xuan"}) );
       set("gender", "女性" );
       set("age", 20);
       set("long","她就是石之轩的女儿石青璇，那天下倾慕的天竹箫就那么随
随便便的搁在膝上，灿烂夺目的阳光从林木间洒落窗前，化
成彷如把她笼罩仙氲霞彩的绿荫中，令人感动得屏息。\n");
       set("combat_exp", 600000);
       set("attitude", "peacuful");
       set_skill("force",170);
       set_skill("parry",170);
       set_skill("dodge",170);
       set_skill("sword",170);
       set_skill("sekong-jianfa",170);
       set("max_gin",3000);
       set("max_sen",3000);
       set("max_kee",3000);
       set("max_force",3000);
       set("force",3000);
       set("inquiry",([
	   "岳山":(:give_msg:),
	   //"不死印":(:do_quest:),
	   "徐子陵":"自从几年前一别，至尽就再也没见过他了。\n",
	   "寇仲":"他和子陵一样行踪不定，我很久没见过他了。\n",
	   //"碧秀心":(:do_action6:),
	   //"遗言":(:do_action7:),
	   "石之轩":"也不知道我爹爹现在在哪里，我也很想见他的。\n",
	   //"扮岳山":(:do_jzzy_quest:),	
	   "邪帝舍利":(:do_action1:),
	   "奖励":(:do_action2:),
	   "切磋":(:do_action3:),
	   "换日大法":(:do_action4:),
	   "岳山遗物":(:do_action5:),
	   ]));
       setup();
 carry_object(__DIR__"obj/cloth")->wear();
 ob=children(__DIR__"obj/xiao");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"你手中的"+ob[i]->query("name")+"被它的主人收回去了！\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"被一阵风卷走了。\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
 carry_object(__DIR__"obj/xiao")->wield();


}
string give_msg()
{
  object ob;
  ob=this_player();
  if(ob->query_skill("badao",1)>=160)
  ob->set_temp("ask_shi",1);
  return "岳山他老人家早就过世了，你去他的坟前看看吧！\n";
}

/*string do_quest()
{
  object ob;
  object book;
  object *inv;
  int i;
  
  ob=this_player();
  if(!ob->query_temp("dtsl_quest_bsy/step2"))
  return "你在说什么啊？我听不懂！\n";
  if(ob->query("dtsl_quest_bsy_ok")){
  book=new("/d/quest/busiyin/obj/busi-yin");
  book->move(ob);
  ob->set_temp("get_busiyin",1);
  tell_object(ob,"石青璇给了你一本《不死印》.\n");
  return "好吧，你拿着本《不死印》去研读吧！\n";}
  if(ob->query_temp("get_busiyin"))
  return "我已经给你书了，你还是好好读吧！\n";
  tell_object(ob,"既然家父已经决定把不死印传授给你，好吧，我带你去！\n");
  inv=all_inventory(ob);
  for(i=0;i<sizeof(inv);i++)
   if(inv[i]->is_character())
    inv[i]->move(environment(ob));
  message_vision(HIC"$N拉着$n的手，身形一晃，向西北方向纵去！\n"NOR,this_object(),ob);
  this_object()->move("/d/quest/busiyin/xiaolu1");
  ob->move("/d/quest/busiyin/xiaolu1");
  message_vision(HIC"$N轻轻说道：前面有四个高手也来抢夺不死印，你把他们杀死就可以了！\n"NOR,this_object());
  message_vision(HIC"$N说罢，如清烟般朝山下飘去。\n"NOR,this_object());
  this_object()->move("/d/chengdu/wu");
  return "世间的纷争本就不少，为何不隐居山林，过些清闲的日子呢？\n";
}
*/
void init()
{
  object ob;
  ob=previous_object();
  if(userp(ob)&&living(ob)&&!ob->is_fighting())
  call_out("welcome",0,ob);
}

void welcome(object ob)
{
  if(!ob||environment(this_object())!=environment(ob)||
     !living(ob)||ob->is_fighting())
     return;
     
  if(ob->query("family/famliy_name")=="花间派"){
   message_vision("$N朝$n笑道：原来是本门中人，快请进来坐坐吧！\n",this_object(),ob);
   return;}
  switch(random(5)){
  
  case 0:message_vision("$N轻轻地叹了口气。\n",this_object());break;
  case 1:message_vision("$N朝$n笑了笑：你能走过树林，也真是了不起了！\n",
         this_object(),ob);break;
  case 2:message_vision("$N轻叹道：江湖的纷争本以够乱，为何没有人喜欢过宁静的日子呢？\n",
         this_object());break;
  case 3:message_vision("$N看着花园中的鲜花，叹道：不知道何时才能看见子陵。\n",
         this_object());break;
  case 4:message_vision("$N叹道：也不知道家父现在怎么样了。\n",this_object());break;
  case 5:message_vision("$N用惊异的眼神看了$n了一眼。\n",this_object(),ob);}
  return;
}

string do_jzzy_quest()
{
  object ob;
  object book;
  
  ob=this_player();
  if(!ob->query_temp("dtsl_quest_jzzy/step8"))
  return "你说的我可是一点也不懂。\n";
  if(ob->query_skill("huanri-dafa",1)<100)
  return "你说的我可是一点也不懂。\n";
  ob->delete_temp("dtsl_quest_jzzy/step8");
  book=new("/d/quest/bawangdao/book2");
  book->move(ob);
  tell_object(ob,query("name")+"给了你一本"+book->query("name")+"\n");
  return "你拿着这个手卷好好领会吧！\n";
}

int do_action1()
{
  object ob,*target;
  int i;
  
  ob=this_player();
  
  if(ob->query_skill("tiandao-bajue",1)>=1){
  	command("say 家父与天刀向来势不两立，你如何能帮我？");
  	return 1;
  }
  
  if(ob->query("perform_quest/badao_fail")){
  	command("say 看来你是帮不了我的，你还是回去吧！");
  	return 1;
  }
  
  if(ob->query_temp("dtsl_quest_badao_killer")>=4){
    command("say 你已经帮我杀了四个邪道高手，太感谢了！");
    return 1;
  }
  if(ob->query("dtsl_quest_badao_ok")){
    command("say 你已经帮过我一次了，实在不敢再麻烦你。");
    return 1;
  }
  
  if(!query("can_kill_enemy")){
    command("say 你问这个想干什么？也想来抢夺吗？？");
    return 1;
  }
     
  command("say 现在有几个邪道高手来我这里抢夺，你如果能帮我，我一定会给你好处的！");
  ob->move("/d/quest/bawangdao/migong1");
  
  target=all_inventory(load_object("/d/quest/bawangdao/migong8"));
  for(i=0;i<sizeof(target);i++)
   if(!userp(target[i]))
    target[i]->set_status(ob);
  delete("can_kill_enemy");
  return 1;
}

void clear_enemy_flag()
{
  remove_call_out("do_clear_enemy_flag");
  call_out("do_clear_enemy_flag",5);
}

void do_clear_enemy_flag()
{
  delete("can_kill_enemy");
  
}

int do_action2()
{
  object ob;
  
  ob=this_player();
  
  if(ob->query("dtsl_quest_badao_ok")){
    command("say 做人不要太贪心啊！");
    command("pat "+ob->query("id"));
    return 1;
  }
  
  if(ob->query_temp("dtsl_quest_badao_killer")<4){
    command("say 四个邪道高手你没杀完，我如何给你好处？");
    return 1;
  }
  ob->delete_temp("dtsl_quest_badao_killer");
  
  if(ob->query_kar()<30){
  	command("say 看你和我没有什么缘分，我还是谢谢你了！");
  	ob->add("perform_quest/badao_fail_times",1);
  	if(ob->query("perform_quest/badao_fail_times")>=2){
  		ob->set("perform_quest/badao_fail",1);
  		command("say 你以后不用来找我了。");
  	}
  	return 1;
  }
  command("thank "+ob->query("id"));
  command("我就将岳老前辈的刀法指点你几招吧！");
  message_vision("\n$N领会了几招霸刀。\n\n",ob);
  ob->set_skill("badao",10);
  ob->set("dtsl_quest_badao_ok",1);
  
  return 1;
}

int do_action3()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query("execute_quest/busiyin_ok")){
    command("say 你没有得到花间的武学精髓，我可不和你切磋！");
    return 1;
  }
  if(ob->query("dtsl_quest_bsy_help_ok")){
    command("say 咱们已经比试过了，我打不过你。");
    return 1;
  }
  
  command("say 好，那咱们就来比试比试吧！");
  ob->set_temp("dtsl_quest_bsy_help_action",1);
  fight_ob(ob);
  
  return 1;
}

int surrender(object killer,object victim)
{
    object *objs,target;
    int i;
    
    if(!killer->query_temp("dtsl_quest_bsy_help_action"))
    return 1;
    
    objs=all_inventory(environment(killer));
    objs=filter_array(objs,(:userp:));
    objs=filter_array(objs,(:$1!=$2:),killer);
    objs=filter_array(objs,(:!$1->query("dtsl_quest_bsy_ok"):));
    objs=filter_array(objs,(:$1->query_temp("dtsl_quest_bsy/step2"):));
    
    killer->set("dtsl_quest_bsy_help_ok",1);
    killer->delete_temp("dtsl_quest_bsy_help_action");
    
    
    if(random(killer->query_quest_kar()+killer->query_kar())<33){
    	command("say 不死印果真名不虚传！");
    	return 1;
    }
    
    if(sizeof(objs)){
       target=objs[random(sizeof(objs))];                                   
       
       message_vision("$N于落败之际突然用出一招！\n",this_object());
       COMBAT_D->do_attack(this_object(),killer,query_temp("weapon"),0,1);
       command("say 我不会不死印，如果会，刚才定会扭转形式。\n");
       if(random(target->query_quest_kar()+target->query_kar())<34){
       	message_vision("$N看了$n的招数，心中有了一些模糊的影子，但终究无法摸清，不由的叹了口气。\n",target,this_object());	
       	target->delete_temp("dtsl_quest_bsy/step2");
       	target->add("execute_quest/busiyin_fail_times",1);
       	if(target->query("execute_quest/busiyin_fail_times")>=2){
       		tell_object(target,HIR"\n你吐出了一口鲜血，看来对这门绝迹是再也无法领会了！\n\n"NOR);
       		target->set("execute_quest/busiyin_fail",1);
       	}
       }
       else{
       	target->set("dtsl_quest_bsy_ok",1);
       	target->set("execute_quest/busiyin",1);
       	target->set("execute_quest/busiyin_ok",1);
       	target->delete_temp("dtsl_quest_bsy/step2");
       	message_vision("$N看了$n的招数，似乎略有所悟！\n",target,this_object());
       }
       
    }
    return 1;
}


int do_action4()
{
  object ob,book;
  
  ob=this_player();
  
  if(ob->query("dtsl_quest_help_huanri_ok")){
    command("say 我不是曾经给过你书吗？怎么又找我来要？？");
    return 1;
  }
  
  if(present("huanri book",ob)){
    command("say 做人不要太贪心啊！");
    command("pat "+ob->query("id"));
    return 1;
  }
  
  if(ob->query_temp("dtsl_quest_badao_killer")<4){
    command("say 四个邪道高手你没杀完，我如何给你好处？");
    return 1;
  }
  if(!ob->query("force_quest/csj1")){
    command("say 这本书就是给了你也没什么用处！\n");
    return 1;
  }
  ob->delete_temp("dtsl_quest_badao_killer");
  command("thank "+ob->query("id"));
  command("好吧，我就给你这本书，不过你未必能看得懂！"); 
  book=new("/d/quest/bawangdao/obj/book");
  book->move(ob);
  message_vision("$N给了$n一"+book->query("unit")+book->query("name")+"。\n",this_object(),ob);
  ob->set("dtsl_quest_help_huanri_ok",1);
  
  return 1;
}

int do_action5()
{
  object ob,book;
  
  ob=this_player();
  
  if(present("yueshan shoujuan",ob)){
    command("say 做人不要太贪心啊！");
    command("pat "+ob->query("id"));
    return 1;
  }
  
  if(ob->query_temp("dtsl_quest_badao_killer")<4){
    command("say 四个邪道高手你没杀完，我如何给你好处？");
    return 1;
  }
  
  ob->delete_temp("dtsl_quest_badao_killer");
  command("thank "+ob->query("id"));
  command("好吧，我就给你岳老前辈的遗物。"); 
  
  book=new("/d/quest/bawangdao/obj/book2");
  book->move(ob);
  message_vision("$N给了$n一"+book->query("unit")+book->query("name")+"。\n",this_object(),ob);
  
  return 1;
  
}

/*int do_action6()
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query("perform_quest/badao")){
    command("say 她是我娘啊，早已去世了，唉... ...");
    return 1;
  }
  
  if(ob->query("dtsl_quest_bsy_help_ok")){
    command("say 她是我娘啊，早已去世了，唉... ...");
    return 1;
  }
  
  if(ob->query_temp("do_bsy_quest2")){
  	command("say 她是我娘啊，早已去世了，唉... ...");
        return 1;
  }
  
  ob->set_temp("do_help_hj_bsy_quest1",1);
  
  command("say 她是我娘啊，早已去世了，我很想念她。");
  
  return 1;
  
}*/
/*
int do_action7()
{
  object ob,obj;
  
  ob=this_player();
  
  if(!ob->query("perform_quest/badao")){
    command("say 你想问谁的遗言？");
    return 1;
  }
  
  if(ob->query("dtsl_quest_bsy_help_ok")){
    command("say 我已经告诉你了，你不要再问了。");
    return 1;
  }
  
  if(!ob->query_temp("do_help_hj_bsy_quest1")){
  	command("say 你想问谁的遗言？");
        return 1;
  }
  
  ob->set_temp("do_help_hj_bsy_quest1",0);
  ob->set("dtsl_quest_bsy_help_ok",1);
  
  obj=new("/d/chengdu/npc/obj/yiyan_book");
  obj->move(ob);
  
  message_vision("$N给了$n一"+obj->query("unit")+obj->query("name")+"。\n",this_object(),ob);
  
  command("say 既然你是岳老前辈的弟子，那我就把我娘的遗言给你看看吧！");
  
  return 1;
  
}*/
