
inherit NPC;
#include <ansi.h>
#include <job_money.h>

void create()
{
   set_name("尤鸟倦",({ "you niaojuan","you"}) );
        set("gender", "男性" );
        set("age", 42);
        set("str",30);
        set("long","这就是邪门高手之一。\n");
        set("combat_exp",600000);
        
        set("max_kee",3000);
        set("max_sen",3000);
        set("max_gin",3000);
        set("max_force",3000);
        set("force",3000);
        set_skill("parry",170);
        set_skill("dodge",170);
        set_skill("force",170);
        
        set_skill("staff",170);
        set_skill("dujiao-tongren",170);
        set_skill("babu-ganchan",170);
    setup();
   carry_object(__DIR__"obj/tongren")->wield();
  
}


#include "job_npc.c"