
inherit F_MASTER;
inherit NPC;
#include <ansi.h>

void create()
{
   set_name("尚公",({ "shang gong","shang","gong" }) );
   set("gender", "男性" );
   set("age", 42);
   set("long", "这是东溟派尊称“尚公”的尚平。\n");
       
    set("combat_exp",3500000);
    set_skill("dodge",300);
    set_skill("parry",300);
    set_skill("force",300);
    set_skill("hammer",300);
    set_skill("strike",300);
   set_skill("youyue-zhangfa",300);
   set_skill("strike",300);
    set_skill("dongming-xinfa",300);
    set_skill("bihai-force",300);
    set_skill("leiting-chuifa",300);
    set_skill("nishang-piaoming",300);
    set_skill("literate",300);
   // set_skill("bencao-shuli",300);

    set("perform_quest/pili",1);
    set("apply_points",2000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: command("perform pili") :),
        (: command("exert shui") :),
        (: command("exert huo") :),
    }));
    set("max_gin",5000);
    set("max_sen",6000);
    set("max_kee",7000);
    set("max_force",9000);
    set("force",9000);
   create_family("东溟派",3,"弟子");
      
   setup();
    carry_object("/obj/cloth/mandongming3")->wear();
   carry_object(__DIR__"obj/hammer")->wield();
  
}

void attempt_apprentice(object ob)
{   
	int lev;
	
	if(ob->query("family"))
	if(ob->query("family/family_name")=="东溟派")
	if((int)ob->query("family/generation",1)<=3)
	{   
	   command("say 此话从何说起？\n");
	   return;
	}
	
	if(ob->query("gender")=="女性"){
	
	command("say 我不收女弟子的！你如果诚心投入本派，去找单霞吧！\n");
	return;
        }
        
        if(ob->query_skill("bihai-force",1)<150){
          command("say 碧海神功是我们东溟派的根基，你不好好学我怎么能收你为弟子呢？");
          return;
        }
        if(ob->query("office_number")<60){
        command("say 你的功绩这么低，我可不要这么懒惰的弟子！\n");
        return;
        }
               
	command("say 近来战乱纷起，我们东溟未必能置身事外，你可以要好好练习武艺，保护我们门派！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "dongming3");
}

