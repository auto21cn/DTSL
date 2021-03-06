
inherit F_MASTER;
inherit NPC;

#include <ansi.h>

int do_quest1();
int do_quest2();
int do_quest3();
int do_quest4();
int do_quest5();
int do_skjf_quest();

void create()
{
   int i;
   object *ob;
   set_name("婠婠",({ "wan wan","wan"}) );
        set("gender", "女性" );
	set("nickname","阴癸仙子");	
        set("age", 22);
   set("long", "这是阴癸派的婠婠，未来阴癸派的继承弟子。\n");
       
   set("combat_exp",1800000);
   set("str", 25);
   set("dex",30);
   set("per", 29);
   
   set_skill("dagger",400);
   set_skill("dodge",400);
   set_skill("parry",400);
   set_skill("force",400);
   set_skill("cuff",400);
   set_skill("literate",400);
   
   set_skill("tianmo-jue",400);
   set_skill("tianmo-dafa",400);
   set_skill("tianmo-huanzong",400);
   set_skill("tianmo-zhan",400);
   
   set("max_gin",3000);
   set("max_kee",3000);
   set("max_sen",3000);
   set("force",3000);
   set("max_force",3000);
   set("perform_quest/lingxiao",1);
   create_family("阴癸派",4,"弟子");
   
   set("inquiry",([
       "天魔斩":(:do_quest1:),
       "师妃喧":(:do_quest2:),
       "天魔凌霄斩":(:do_quest3:),
       "徐子陵":(:do_quest4:),
       "挑战":(:do_quest5:),
       "正邪之战":(:do_skjf_quest:),
       ]));
       
   setup();
   
   ob=children(__DIR__"obj/dagger");
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
   carry_object(__DIR__"obj/dagger")->wield();
  
}
void attempt_apprentice(object ob)
{
	
	int lev;
	
	if(ob->query("family"))
	if(ob->query("family/family_name")=="阴癸派")
	if((int)ob->query("family/generation",1)<=4)
	{   
	   command("say 此话从何说起？\n");
	   return;
	}
	if(ob->query("gender")=="男性"){
	
	command("say 我不收男弟子的！你如果诚心投入本派，去找林士宏吧！\n");
	return;
        }
        
        
        if(ob->query_skill("tianmo-dafa",1)<150){
        command("say 你的天魔大法修为不够，还是再去修习一下再拜我为师吧！\n");
        return;
        }
     
        if(ob->query("office_number")<60){
        command("say 你的功绩这么低，我可不要这么懒惰的弟子！\n");
        return;
        }
        if(ob->query("bellicosity")<1000){
        command("say 你的杀气不够多，如何成为我门下的魔门弟子？\n");
        return;
        }
        if(ob->query_per()<30){
	 command("hmm1");
	 command("say 你的样子不够漂亮，我可不收这样的弟子！\n");
	 return;
	}
        
        if(!ob->query_temp("bai_wanwan")){
          ob->set_temp("bai_wanwan_step1",1);
          command("say 最近我想需要一些香料，不知道"+RANK_D->query_respect(ob)+
                 "能不能帮我弄来？");
          return;
        }

        lev=ob->query_skill("cuff",1);
        lev=lev*lev/(lev+100);
        ob->party_reward_skill("dagger",lev);
        tell_object(ob,HIY"你从基本拳法中领略到了基本匕法！\n"NOR);
               
	command("say 好！希望你将来能一统魔道，长我阴癸派名声！\n");
	command("recruit "+ob->query("id"));
	ob->delete_temp("bai_wanwan");
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "yin_guan");
}

int accept_object(object ob,object obj)
{
    string msg;
    
    if(!ob->query_temp("bai_wanwan_step1"))
    return 0;
    if(obj->query("order")!=2)
    return 0;
    ob->add_temp("bai_wanwan_goods",1);
    if(ob->query_temp("bai_wanwan_goods")==1){
      msg="$N朝$n微微一笑：谢谢你了！\n";
    }
    else
    if(ob->query_temp("bai_wanwan_goods")==2){
      msg="$N展颜道：麻烦"+RANK_D->query_respect(ob)+"了。\n";      
    }
    else{
      msg="$N道：真是感谢，"+RANK_D->query_respect(ob)+"心地不错，\n"+
          "以后想学什么就到大师姐这里来吧。\n"; 
          ob->set_temp("bai_wanwan",1);
      ob->delete_temp("bai_wanwan_goods");
      ob->delete_temp("bai_wanwan_step1");
    }
    message_vision(msg,this_object(),ob);

    return 1;
}
    

int do_quest1()
{
   object ob;
   string msg;
   int flag;
   
   ob=this_player();
   
   if(ob->query("perform_quest/lingxiao")){
     command("say 你已经领会了天魔斩的诀窍，以后的提高就看你自己了！");
     return 1;
   }
   if(ob->query("perform_quest/wanhuan")){
     command("say 你已经领会了千变铜萧的诀窍，无法再领会天魔斩的诀窍了！");
     return 1;
   }
   if(ob->query("perform_quest/yulong")){
     command("say 你已经领会了天魔带的诀窍，无法再领会天魔斩的诀窍了！");
     return 1;
   }
   if(ob->query_skill("tianmo-zhen",1)){
     command("say 你学了天魔阵，无法再学习天魔斩的诀窍了！");
     return 1;
   }
   
   if(ob->query_skill("tianmo-zhan",1)<160){
      command("pat "+ob->query("id"));
      command("say 你的「天魔斩」修为太低了，现在还不能领会其中的诀窍！");
      return 1;
   }
   
   
   msg="$N横了$n一眼，突然咯咯的笑了起来，来来来，教教你怎么在战斗中挨刀子！\n";
   message_vision(msg,this_object(),ob); 
   
   flag=COMBAT_D->do_attack(this_object(),ob,query_temp("weapon"),0,2);
   
   if(!flag){
     msg="$N对$n怒道：既然你本领这么高强，还找我来做什么？\n";
     message_vision(msg,this_object(),ob); 
     return 1;
   }
   ob->set_temp("tianmz_quest1",1);
   command("whisper "+ob->query("id")+" "+"天魔斩的诀窍是以身入敌，你可要记牢了！");
   return 1;
}

int do_quest2()
{
   object ob;
   
   ob=this_player();
   
   if(!ob->query_temp("tianmz_quest1")){
     command("sigh");
     command("say 师妃喧的武功高强，我也未必能完胜她啊！");
     return 1;
   }
   ob->delete_temp("tianmz_quest1");
   ob->set_temp("tianmz_quest2",1);
   command("say 我刚刚从四川回来，还和她打了一架！");
   message_vision("$N甜甜一笑。\n",this_object());
   return 1;
}

int do_quest3()
{
   object ob;
   string msg;
   
   ob=this_player();
   
   if(!ob->query_temp("tianmz_quest2")){
     command("say 这是天魔斩的绝学，你未必能领会得了！");
     return 1;
   }
   ob->delete_temp("tianmz_quest2");
   ob->set_temp("tianmz_quest3",1);
   msg="$N朝$n哦了一声：来来来，今天师傅心情好，和我玩玩。说着噗哧一笑，\n"+
       "象是想到了什么开心事。\n"; 

   message_vision(msg,this_object(),ob);
   return 1;
}

int surrender(object killer,object victim)
{
     string msg;
         
     if(killer->query_temp("tianmz_quest5")){
     	msg="$N强作欢容：唉，你的天魔斩练的已经差不多了，就是攻击力差了一点... ...\n"+
     	    "看上去$N有些心事，$n望着她那绝美的脸颊，带着凄美的玉容，胸中气血翻滚，\n"+
     	    "那雨雪深处，白衣如雪，裙下赤足的景象，渐渐在心底清晰，不由心有所悟。\n";
     	message_vision(msg,this_object(),killer);
     	killer->set("perform_quest/lingxiao",1);
     	killer->save();
     	killer->delete_temp("tianmz_quest5");
     	return 1;
     }

     
     if(!killer->query_temp("tianmz_quest3"))
     return 1;
     command("heng");
     return 1;
}

int end_fight(object killer,object victim)
{
   string msg;
   
   if(!victim->query_temp("tianmz_quest3"))
   return 1;
   
   msg="$N对$n说：嘻嘻，你怎么靠一身皮来施展凌霄斩啊，天魔凌霄斩心法是游龙四伏，\n"+
       "八面埋伏，击敌必中，杀敌必死，上次是我骗你的。\n";
   message_vision(msg,killer,victim);
   victim->delete_temp("tianmz_quest3");
   victim->set_temp("tianmz_quest4",1);
   return 1;
}

int do_quest4()
{
   object ob;
   string msg;
   
   ob=this_player();
   
   if(!ob->query_temp("tianmz_quest4")){
     command("say 我很久没看到他了，人家很想他啊！");
     return 1;
   }
   ob->delete_temp("tianmz_quest4");
   ob->set_temp("tianmz_quest5",1);
   
   msg="$N叹了一口气，我已经十年没有见过他了，不知道他和清璇现在可好？\n";
   message_vision(msg,this_object(),ob);
   return 1;
}

int do_quest5()
{
   object ob;
   string msg;
   
   ob=this_player();
   
   if(!ob->query_temp("tianmz_quest5")){
     command("say 你打不过我的，用不着挑战了！");
     return 1;
   }
   fight_ob(ob);
   return 1;
}

int do_skjf_quest()
{
   object ob,target,*guards;
   string msg;
   
   ob=this_player();
   
   if(!ob->query_temp("perform_quest/kong_action3")){
     command("say 凭你也想来问正邪之战？你还差的远呢！");
     return 1;
   }
   guards=ob->query_temp("guarded");
   if(!arrayp(guards)){
    command("say 就你自己也想战胜我？不可能的！");
    return 1;
   }
   if(guards)
   guards=guards-({0});
   if(sizeof(guards)>1){
     command("say 带了这么多帮手，算什么啊？");
     return 1;
   }
   target=guards[random(sizeof(guards))];
   if(!objectp(target)||environment(target)!=environment(ob)){
     command("say 就你自己也想战胜我？不可能的！");
     return 1;
   }
   if(target->query("combat_exp")<1000000){
     command("say 你的帮手武功太弱了吧！");
     return 1;
   }
   if(target->query("famous")<2000){
     command("say 你的帮手没什么名气啊，换一个吧！");
     return 1;
   }
   if(target->query("gender")=="女性"){
     command("say 你还找个男帮手来吧！");
     return 1;
   }
   if(environment(ob)->query("no_death")){
     command("say 这个地方来战斗不合适吧！");
     return 1;
   }
   
   msg="\n$N笑道：好吧，既然这段恩怨总要了结，那就开始吧！\n"+
       "$N突然向$n发动攻击！\n"+
       target->name()+"纵身一跃，挡在了$n面前！\n"+
       "$N天魔气场一发，"+target->name()+"无法躲闪，已经陷入了死地！\n";
   message_vision(msg,this_object(),ob);
   target->die();
   
   "/cmds/std/go.c"->do_flee(ob);
   
   msg="\n$N突然领悟出人世间四大皆空、虚无飘渺的道理来！\n";
   message_vision(msg,ob);
   ob->delete_temp("perform_quest/kong_action3");
   ob->set("perform_quest/kong",1);
   
   return 1;
}
