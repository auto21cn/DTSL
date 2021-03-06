
inherit F_MASTER;
inherit NPC;
void create()
{
   set_name("云长老",({ "yun zhanglao","yun" }) );
        set("gender", "男性" );
		
        set("age", 42);
   set("long", "他就是阴癸派的云长老,他的邪功可以说的上是一流。\n");
       
   set("combat_exp",300000);
   set("str", 25);
   set("per", 22);
   set("attitude", "peaceful");
   set_skill("unarmed",120);
   set_skill("dodge",120);
   set_skill("parry",120);
   set_skill("force",150);
   set_skill("sword",150);
   set_skill("strike",150);
   set_skill("cuff",150);
   set_skill("jiutian-huanzhang",150);
   set_skill("literate",150);
   set_skill("tianmo-dafa",150);
   set_skill("tianmo-jianfa",130);
   set_skill("tianmo-huanzong",130);
   set_skill("tianmo-dai",120);
   set("dodge",({"tianmo-huanzong"}));
   set("force_skill",({"tianmo-dafa"}));
   set("sword",({"tianmo-jianfa"}));
   set("hand",({"tianmo-dai","jiutian-huanzhang"}));
   set("gin",1000);
   set("max_gin",1000);
   set("kee",1000);
   set("max_kee",1000);
   set("sen",1000);
   set("max_sen",1000);
   set("force",1500);
   set("max_force",1500);
   create_family("阴癸派",5,"长老");
   set("class","yin1");
   setup();
   carry_object(__DIR__"obj/caiyi")->wear();
   carry_object(__DIR__"obj/changjian")->wield();
  
}
void attempt_apprentice(object ob)
{   
	if(ob->query("family"))
	if(ob->query("family/family_name")=="阴癸派")
	if((int)ob->query("family/generation",1)<5)
	{   if(ob->query("gender")=="男性")
		tell_object(ob,"云长老连忙笑道:师兄真是会开玩笑!\n");
	    else tell_object(ob,"云长老连忙笑道:师姐真是会开玩笑!\n");
		return;
	}
	if(ob->query("shen")>0)
	{
		tell_object(ob,"云长老冷笑道:像你这种正派人士,我们阴癸派可是不要!\n");
		return;
	}
	command("say 好,只要在阴癸派好好干,保证你将来啸傲江湖!\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "yin1");
}

