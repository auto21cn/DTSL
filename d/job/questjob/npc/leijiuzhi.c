
inherit NPC;

#include <ansi.h>
#include <job_money.h>

void create()
{
   set_name("雷九指",({ "lei jiuzhi","lei"}) );
        set("gender", "男性" );
        set("age",55);
     	
   set("long", "这是雷九指，据说他赌术高超，少有敌手。\n");
       
   set("combat_exp", 30000);
   set("str", 20);
   set("per", 10);
   
   set_skill("strike",100);
   set_skill("dodge",100);
   set_skill("parry",100);
   set_skill("force",100);
   set_skill("cuff",100);
   set_skill("finger",100);
   
   set_skill("jiutian-huanzhang",100);
   set_skill("baihua-zhang",100);
   set_skill("dujie-zhi",100);
   set_skill("linglong-yuquan",100);
   set_skill("tianmo-huanzong",100);
   
   set("max_kee",2000);
   set("max_gin",2000);
   set("max_sen",2000);
   set("force",2000);
   set("max_force",2000);
   setup();
  
}



#include "job_npc.c"