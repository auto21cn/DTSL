inherit NPC;
#include <ansi.h>
void create()
{
   set_name("红拂女",({ "hongfu nv","hongfu" }) );
        set("gender", "女性" );
	set("age", 25);
   set("long", "这是天策府的上将，谁都不知道她的名字，\n"+
               "因其兵器是一根红拂，故呼之为红拂女。\n");
       
   set("combat_exp",800000);
   set("str", 25);
   set("per", 25);
   set("attitude", "peaceful");
   set_skill("whip",180);
   set_skill("dodge",180);
   set_skill("parry",180);
   set_skill("force",180);
   set_skill("shuiyun-xiufa",180);
   set_skill("nishang-piaoming",180);
 
   set("max_gin",2000);
   set("max_sen",2000);
   set("max_kee",2000);
   set("force",2000);
   set("max_force",2000);
   setup();
   carry_object(__DIR__"obj/whip")->wield();
  
}
