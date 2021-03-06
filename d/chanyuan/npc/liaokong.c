
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string do_quest();
string give_key();
int do_action1();
int do_answer(string arg);
int do_action2();

void create()
{
   set_name("了空",({ "liao kong","liao","kong"}));
        set("gender", "男性" );
        set("age", 52);
   set("long", "他就是净念禅院的主持了空大师。\n");
   set("class","bonze"); 
   set("combat_exp",1500000);
   set("str", 28);
   set("per", 25);
   
   set_skill("dodge",400);
   set_skill("parry",400);
   set_skill("force",400);
   set_skill("staff",400);
   set_skill("cuff",400);
   set_skill("finger",400);
   set_skill("strike",400);

   set_skill("tiangang-quan",400);
   set_skill("fumo-zhangfa",400);
   set_skill("dujie-zhi",400);
   set_skill("rulai-shenzhang",400);
   set_skill("lianhua-step",400);

   set_skill("literate",400);
   set_skill("chanzong-fofa",410);
   set_skill("wuxiang-shengong",400);
   set_skill("bikouchan",400);


    set("perform_quest/liudao",1);
    set("perform_quest/pudu",1);
    set("perform_quest/tiangang",1);
    set("apply_points",2000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: command("perform liudao") :),
        (: command("perform pudu") :),
        (: command("perform tiangang") :),
        (: command("execute wuyu") :),
    }));

    set("max_gin",3000);
    set("max_sen",5000);
    set("max_kee",5000);
    set("max_force",10000);
    set("force",7000);

   
   create_family("净念禅院",3,"掌门");
  
   set("inquiry",([
     "超越":(:do_quest:),
     "密室":(:give_key:),
     "考验":(:do_action1:),
     "赎罪":(:do_action2:),
     ]));
   setup();
  
}

void init()
{
   add_action("do_answer","answer");
}


void attempt_apprentice(object ob)
{   
	
	if(ob->query("family")
	   &&ob->query("family/family_name")=="净念禅院"
	   &&ob->query("family/generation",1)<=3){
	    command("say 你可真会开玩笑！");
	    return;
	}
	if(ob->query("gender")=="女性")
	{
	    command("say 唉，施主身为女子之身，不便与男弟子学习佛法。若施主真心希望\n"+
	            "归依佛门大可到慈航静斋。");
	    return;
	}
	if(ob->query("couple")){
	  command("say 身为人夫却不尽夫之责任，我们净念禅院不要如此不仁不义之徒。");
	  return;
	}
	if((int)ob->query("PKS",1)>=5)
	{
		command("say 施主你作孽深重，我如何收你为徒呢！");
		return;
	}
	if(ob->query("bellicosity")>=100){
	  command("say 施主身上杀气重重，如何能专心归依佛门呢！");
	  return;
	}
	if(ob->query_skill("wuxiang-shengong",1)<150){
	  command("say 你的「无相神功」修为太低了，还是去学习一下再拜我为师吧！");
	  return;
	}
	if(ob->query("office_number")<50){
	  command("say 你的功绩太低了，我不喜欢懒惰的弟子！");
	  return;
	}
	if(ob->query("family/generation",1)>5){
	  command("say 你的辈分太低了，如何拜我为师？");
	  return;
	}
	if(!ob->query_temp("try_bai_liaokong_ok")){
	  command("say 你没经过我的考验，我不会收你为徒的。");
	  return;
	}
	
	
	command("say 阿弥陀佛！希望你今后能超度世人的苦恼，成为一代高僧，光大佛法！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "bonze");
}

string do_quest()
{
  object ob,obj;
  
  ob=this_player();
  if(ob->query_skill("wuxiang-shengong",1)<200)
  return "你的功夫太低了，现在还无法超越的！\n";
  if(ob->query("family_lingwu")=="chanyuan")
  return "长江后浪推前浪，你已经超越我了，还是快去领悟吧！\n";
  
  if(ob->query_temp("quest_fighter"))
  return "你还是快点战胜木人吧！\n";
  ob->set_temp("gage_liaokong",1);
  
  obj=new(__DIR__"q_liaokong");
  obj->set("name",ob->name()+"的木人");
  obj->set("target_id",ob->query("id"));
  obj->set_temp("owner_ob",ob);
  ob->set_temp("quest_fighter",obj);
  ob->add_temp_array("job_temp_killer",obj);
  obj->move(environment(ob));
  
  return "好小子，有骨气，不过你要想超越我，就必须赢了这个木人！\n";
}
/*
string no_color(string arg)
{
        arg = replace_string(arg,  BLK, "");
	arg = replace_string(arg,  RED, "");
	arg = replace_string(arg,  GRN, "");
	arg = replace_string(arg,  YEL, "");
	arg = replace_string(arg,  BLU, "");
	arg = replace_string(arg,  MAG, "");
	arg = replace_string(arg,  CYN, "");
	arg = replace_string(arg,  WHT, "");
	arg = replace_string(arg,  HIR, "");
	arg = replace_string(arg,  HIG, "");
	arg = replace_string(arg,  HIY, "");
	arg = replace_string(arg,  HIB, "");
	arg = replace_string(arg,  HIM, "");
	arg = replace_string(arg,  HIC, "");
	arg = replace_string(arg,  HIW, "");
	arg = replace_string(arg,  NOR, "");
	arg = replace_string(arg,  BLINK, "");
	return arg;
}


int surrender(object killer,object victim)
{
   object ob;
   string newname;
   
   if(!killer->query_temp("gage_liaokong"))
   return 1;
   message("vision",HIG"【静念禅院】:了空拉着"+killer->name()+HIG+"的手，热泪盈眶，嘱咐道：你一定要光大佛法，造福百姓！\n"NOR,users());
   
   newname=killer->query("name");
   newname=no_color(newname);
   newname="了"+newname[2..3];
   killer->set("name",newname);
   killer->set("family/generation",3);
   tell_object(killer,HIY"你的名字以后是"+newname+"，你成为了禅院第三代弟子！\n"NOR);
   
   message_vision(YEL"$N拍了拍$n的肩膀，我佛终于后代有人了！我告诉你一个秘密！\n"NOR,victim,killer);
   tell_object(killer,"了空凑到你的跟前，对你耳语道：我佛前辈曾留下一个密室，现在就看你的造化了！\n");
   ob=new("/d/clone/room/lingwu/chanyuan/key");
   ob->move(killer);
   killer->set("family_lingwu","chanyuan");
   killer->set("title","静念圣僧");
   tell_object(killer,"了空给了你一个黄金钥匙。\n");
   return 1;
}
int end_fight(object killer,object victim)
{
  if(!victim->query_temp("gage_liaokong"))
   return 1;
  message_vision("$N朝$n叹了口气，你还是回去再磨练磨练吧！\n",killer,victim);
  return 1;
}
*/
string give_key()
{
  object ob,key;
  ob=this_player();
  if(ob->query("pker"))
  return "我佛门出了你这样的通缉犯，真是不幸啊！\n";
  if(ob->query("family_lingwu")!="chanyuan")
  return "你在说什么，贫僧可是一点都不懂啊！\n";
  if(objectp(key=present("key",ob)))
    if(key->query("unique"))
    return "你已经有钥匙了，快去学习吧！\n";
  key=new("/d/clone/room/lingwu/chanyuan/key");
  key->move(ob);
  tell_object(ob,"了空给了你一个黄金钥匙。\n");
  return "希望你能光大佛法，造福百姓！\n";
}

int do_action1()
{
   object ob;
   string msg;
   
   ob=this_player();
   
        if(ob->query("family")
	   &&ob->query("family/family_name")=="净念禅院"
	   &&ob->query("family/generation",1)<=3){
	    command("say 你可真会开玩笑！");
	    return 1;
	}
        
        if(ob->query("family/generation")<=4){
          command("say 你已经经过考验，无须再次考验了！");
          return 1;
        }
        
	if(ob->query("gender")=="女性")
	{
	    command("say 唉，施主身为女子之身，不便与男弟子学习佛法。若施主真心希望\n"+
	            "归依佛门大可到慈航静斋。");
	    return 1;
	}
	
	if(ob->query("couple")){
	  command("say 身为人夫却不尽夫之责任，我们净念禅院不要如此不仁不义之徒。");
	  return 1;
	}
	
	if((int)ob->query("PKS",1)>=5)
	{
		command("say 施主你作孽深重，我如何收你为徒呢！");
		return 1;
	}
	
	if(ob->query("bellicosity")>=100){
	  command("say 施主身上杀气重重，如何能专心归依佛门呢！");
	  return 1;
	}
	if(ob->query_skill("wuxiang-shengong",1)<150){
	  command("say 你的「无相神功」修为太低了，还是去学习一下再拜我为师吧！");
	  return 1;
	}
	if(ob->query("office_number")<50){
	  command("say 你的功绩太低了，我不喜欢懒惰的弟子！");
	  return 1;
	}
	if(ob->query("family/generation",1)>5){
	  command("say 你的辈分太低了，如何拜我为师？");
	  return 1;
	}
	
	msg="$N微睁双目，朝$n道：悟否？\n";
	message_vision(msg,this_object(),ob);
	ob->set_temp("try_bai_liaokong_action1",1);
	return 1;
}

#define ANSWER "菩提本非树，明镜亦非台。本来无一物，何处惹尘埃？"


int do_answer(string arg)
{
  object ob;
  
  ob=this_player();
  
  if(!ob->query_temp("try_bai_liaokong_action1"))
  return 0;
  if(!arg)
  return notify_fail("你悟出了什么？\n");
  if(arg!=ANSWER)
  return notify_fail(query("name")+"微微摇了摇头，闭口不语。\n");
  message_vision("$N微微一笑，点了点头。\n",this_object());
  ob->set_temp("try_bai_liaokong_ok",1);
  ob->delete_temp("try_bai_liaokong_action1");
  return 1;
}

int do_action2()
{
  object ob;
  string msg;
  
  ob=this_player();
  
  if(ob->query("class")!="bonze"){
   command("say 你还是先出家再赎罪吧！");
   return 1;
  }
  if(ob->query("PKS")<=0){
    command("say 你没有开杀戒，不用赎罪。");
    return 1;
  }
  command("say 既然你已经犯下重重罪孽，唯有入地狱方能赎罪了！");
  msg="\n$N跪在地上，低声诵道：阿弥陀佛！\n\n"+
      "$n诵道：苦海无边，回头是岸！\n\n"+
      "$N痛苦的一笑，全身内力激撞起来！\n"+
      "只听喀喀声响，$N全身骨骼尽数碎裂！\n\n";
  message_vision(msg,ob,this_object());
  ob->set_temp("last_damage_msg",ob->name()+"赎罪自尽了！");
  ob->delete_temp("last_damage_from");
  ob->add("PKS",-1);
  ob->die();
  ob->delete_temp("last_damage_msg");
  ob->set("last_damage_msg","赎罪自尽");
  return 1;
}
