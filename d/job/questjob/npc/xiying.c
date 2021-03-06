
inherit NPC;

#include <ansi.h>
#include <job_money.h>

void create()
{
   set_name("席应",({ "xi ying","xi"}) );
        set("gender", "男性" );
        set("age",40);
        set("nickname","天君");
		
   set("long", "这是人称天君的席应，近日重反中原。\n"+
               "他一身青衣，作文士打扮，硕长高瘦，\n"+
               "表面看去一派文质彬彬，举止文雅，白\n"+
               "哲清瘦的脸上挂著微笑，但只要看清楚\n"+
               "他浓密的眉毛下那对份外引人注目的眼\n"+
               "睛，便可发觉内中透出邪恶和残忍。\n");
       
   set("combat_exp", 30000);
   set("str", 20);
   set("per", 10);
   
   set_skill("strike",100);
   set_skill("dodge",100);
   set_skill("parry",100);
   set_skill("force",100);
   
   set_skill("ziqi-tianluo",100);
   set_skill("niaozong-shu",100);
   
   set("max_kee",2000);
   set("max_gin",2000);
   set("max_sen",2000);
   set("force",2000);
   set("max_force",2000);
   setup();
  
}



#include "job_npc.c"