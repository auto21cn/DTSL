#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string do_quest1();
string do_quest2();
void create()
{
   set_name("梵清惠",({ "fan qinghui","fan" }) );
        set("gender", "女性" );
        set("age",42);
   set("long", "这是慈航静斋的掌门梵清惠。\n");
       
   set("combat_exp",3500000);
   set("str", 25);
   set("per",25);
   set("max_gin",5000);
   set("max_kee",5000);
   set("max_sen",5000);
   set("max_force",5000);
   set("force",5000);
   set("attitude", "peaceful");
   set_skill("sword",480);
   set_skill("cuff",480);
   set_skill("parry",480);
   set_skill("strike",480);
   set_skill("dodge",480);
   set_skill("finger",480);
   set_skill("literate",480);
   set_skill("force",480);
   set_skill("sekong-jianfa",480);      
   set_skill("xiuluo-zhi",480);
   set_skill("wuwang-jing",500);
   set_skill("qingxin-force",480);
   set_skill("lingyun-shenfa",480);
  
   create_family("慈航静斋",2,"掌门");
   set("inquiry",([
      "玄女":(:do_quest1:),
      "任务":(:do_quest2:),
      ]));
   set("class","bonze");
   setup();
   carry_object(__DIR__"daopao")->wear();
   carry_object(__DIR__"changjian")->wield();
  
}

void attempt_apprentice(object ob)
{   
	
	if(ob->query("gender")=="男性")
	{
	  command("say 我们慈航静斋不收男弟子的，如果你一心向佛，去净念禅院吧！\n");
	  return;
	}
	if(ob->query("family")&&ob->query("family/family_name")=="慈航静斋"
	  &&ob->query("family/generation")<=2)
	{
	  command("say 这话从何说起？\n");
	  return;
	}
	if(ob->query("kar")<24)
	{
	  command("say 唉，看你面象于佛无缘，你还是投靠其他门派吧！\n");
	  return;
	}
	if(ob->query_int()<31)
	{
	  command("say 你的头脑不够聪明啊，好好学学再来吧！\n");
	  return;
	 }
       if(ob->query("PKS")>=5){
	  command("say 你身上罪孽太多，我可不要这样的弟子！");
	  return;
	}
	
	if(ob->query("bellicosity")>=100){
	  command("say 你身上杀气重重，如何修炼本门的武功？");
	  return;
	}
       if(ob->query_skill("qingxin-force",1)<200)
       {
       	 command("say 你的清心普善诀修炼还不够，继续去修炼吧！\n");
       	 return;
       	}
       	
       	if(ob->query("couple")){
       	command("say 既然你已经成婚出嫁，还是不要拜到我的门下吧！\n");
       	return;}
       
       if(ob->query("office_number")<40){
        command("say 你的功绩这么低，我可不要这么懒惰的弟子！\n");
        return;
      }

       if(!ob->query_temp("try_recruit")){
       	command("say 入我门下，必须出家，你还是好好想想吧！\n");
       	ob->set_temp("try_recruit",1);
       	return;}
       	ob->delete_temp("try_recruit");
             
       	command("say 好，看来你已经想好了！\n");
	command("say 好,既然能拜到我的门下，说明你真的能够忍受修炼的艰苦!\n");
	command("say 希望你以后能普善济世，为武林造福！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "bonze");
}

string do_quest1()
{
  object ob;
  ob=this_player();
  
  if(ob->query("family_lingwu")=="jingzhai")
  return "你已经是本门玄女了，直接去密室领悟吧！\n";
  
  if(ob->query_temp("dtsl_fquest_jz/step6")){
    ob->delete_temp("dtsl_fquest_jz");
    ob->set("family_lingwu","jingzhai");
    ob->set("title","玄女");
    message("vision",HIG"【慈航静斋】:"+query("name")+"喜道:希望本门玄女"+ob->name()+HIG+
    "能早日协助明君平定天下，使百姓安居乐业！\n"NOR,users());
    ob->reward_family_point();
   return "你去旁边的密室去领悟吧！能不能进去，就看你的造化了！\n";
  
  }
   
  if(!ob->query_temp("dtsl_fquest_jz/step3"))
  return "是否能成为本门的玄女，你必须先战胜本门弟子师妃喧！\n";
  ob->delete_temp("dtsl_fquest_jz/step3");
  ob->set_temp("dtsl_fquest_jz/step4",1);
  return "好吧，想成为本门玄女，还要为天下百姓做一件事才可以。\n";
}

string do_quest2()
{
  object ob;
  object letter;
  ob=this_player();
  if(!ob->query_temp("dtsl_fquest_jz/step4"))
  return "你说的什么？我可一点也听不懂啊！\n";
  ob->delete_temp("dtsl_fquest_jz/step4");
  ob->set_temp("dtsl_fquest_jz/step5",1);
  letter=new(__DIR__"letter");
  letter->move(ob);
  return "好吧，你去把这封书信送给(song)未来天下的名君，然后回来复命吧！\n";
}
