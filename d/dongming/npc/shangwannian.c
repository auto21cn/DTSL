
inherit NPC;
#include <ansi.h>
void create()
{
   set_name("尚万年",({ "shang wannian","shang","wannian" }) );
   set("gender", "男性" );
   set("nickname","护派战将");
   set("age", 23);
   set("long", "这是东溟派的护派四将之一。\n");
       
   set("combat_exp",100000);
   set_skill("dodge",100);
   set_skill("parry",100);
   set_skill("force",100);
   set_skill("strike",100);
   
   set_skill("dongming-xinfa",100);
   set_skill("bihai-force",100);
   set_skill("youyue-zhangfa",100);
   set_skill("nishang-piaoming",100);
   set_skill("literate",100);
  
   set("max_gin",1000);
   set("max_sen",1000);
   set("max_kee",1000);
   set("force",1000);
   set("max_force",1000);
   create_family("东溟派",7,"弟子");
   setup();
  
}
