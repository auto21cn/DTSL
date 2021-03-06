
inherit F_MASTER;
inherit NPC;

#include <ansi.h>

int do_action1();

void create()
{
   set_name("墩欲谷",({ "dun yugu","dun" }) );
   set("gender", "男性" );
   set("age", 42);
   
   set("long", "他就是毕玄的弟弟，深得突厥大汗的信任．\n");
       
   set("combat_exp",1000000);
 
   set_skill("dodge",200);
   set_skill("parry",200);
   set_skill("force",200);
   set_skill("whip",200);
   set_skill("literate",200);
  
   set_skill("yanyang-dafa",200);
   set_skill("canglang-jue",200);
   set_skill("youlong-shenfa",200);
   set_skill("feiwo-whip",200);
   set("max_gin",3000);
   set("max_kee",3000);
   set("max_sen",3000);
   set("force",3000);
   set("max_force",3000);
   create_family("突厥",3,"武士");
   set("inquiry",([
    "考验":(:do_action1:),
    ]));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
   carry_object(__DIR__"obj/whip")->wield();
  
}
void attempt_apprentice(object ob)
{   
	
	if(ob->query("family"))
	if(ob->query("family/family_name")=="突厥")
	if((int)ob->query("family/generation",1)<=3)
	{   
	  command("say 此话从何说起？");
	  return;
	}
	if(ob->query("tujue_jun")!="金狼军"){
            command("say 你没加入我们金狼军，我可不要你这样的徒弟！");
            return;
        }
        if(ob->query_skill("yanyang-dafa",1)<150){
            command("say 你的炎阳大法修为太低了，叫我如何收你为徒？");
            return;
        }
        if(ob->query("office_number")<40){
        command("say 你的功绩这么低，我可不要这么懒惰的弟子！\n");
        return;
        }
        if(!ob->query_temp("bai_dun_ok")){
          command("say 你没经过考验，我怎么能收你？");
          return;
        }
        ob->delete_temp("bai_dun_ok");
     
	command("say 你可要努力学习武功，将来为突厥一统中原尽力！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "tujue3");
}

int do_action1()
{
  object ob;
  
  ob=this_player();
  
  if(ob->query("family")
  &&ob->query("family/family_name")!="突厥"
    ){
    command("say 你真是说笑了！");
    return 1;
  }
  if(ob->query("family"))
	if(ob->query("family/family_name")=="突厥")
	if((int)ob->query("family/generation",1)<=4)
	{   
	  command("say 此话从何说起？");
	  return 1;
	}
  if(!ob->query("family")
    ){
    command("say 你还不是我突厥弟子，如何接受我的考验？");
    return 1;
  }
  
  if(ob->query("tujue_jun")=="黑狼军"){
      command("say 你既然已经加入了黑狼军，就休想再为我办事！");
      return 1;
  }
  if(ob->query_temp("bai_dun_ok")){
     command("say 你已经经过考验了。");
     return 1;
  }
  
  ob->set_temp("bai_dun",1);
  command("say 我想养一只小鹰，你能不能给我找一个？");
  
  return 1;
}

int accept_object(object ob,object obj)
{
   if(!ob->query_temp("bai_dun"))
    return 0;
   if(!obj->query("bai_dun_quest_obj2"))
   return 0;
   
   ob->delete_temp("bai_dun");
   ob->set_temp("bai_dun_ok",1);
   command("say 谢谢你了！");
   return 1;
}