
inherit NPC;
inherit F_MASTER;

#include <ansi.h>

void create()
{
   set_name("葛云清",({ "ge yunqing","ge" }) );
   set("gender", "女性" );
   set("age", 22);
   set("long", "这是慈航静斋的葛云清。\n");
       
   set("combat_exp",100000);
   set("int", 25);
   set("per", 26);
   set("max_gin",1000);
   set("max_kee",1000);
   set("max_sen",1000);
   set("max_force",1000);
   set("force",1000);
  
   set_skill("dodge",100);
   set_skill("finger",100);
   set_skill("literate",100);
   set_skill("force",100);
   set_skill("parry",100);
   set_skill("xiuluo-zhi",100);
   set_skill("wuwang-jing",110);
   set_skill("qingxin-force",100);
   set_skill("lingyun-shenfa",100);
  
   create_family("慈航静斋",6,"弟子");
   setup();
   carry_object(__DIR__"obj/baiyi")->wear();
  
}

void attempt_apprentice(object ob)
{   
	
	if(ob->query("gender")=="男性")
	{
	  command("say 我们慈航静斋不收男弟子的，如果你一心向佛，去净念禅院吧！\n");
	  return;
	}
	if(ob->query("family")&&ob->query("family/family_name")=="慈航静斋"
	  &&ob->query("family/generation")<=6)
	{
	  command("say 这话从何说起？\n");
	  return;
	}
	if(ob->query("kar")<24)
	{
	  command("say 唉，看你面象于佛无缘，你还是投靠其他门派吧！\n");
	  return;
	}
	if(ob->query("per")<25){
	  command("say 你的相貌太差了，我可不要这样的弟子！");
	  return;
	}
	if(ob->query_int()<25)
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
	
	command("say 慈航静斋的修炼非常艰苦，希望你持之以恒，光大我派佛法武学！\n");
	
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "jingzhai1");
}
