
inherit NPC;
#include <ansi.h>

void create()
{
       set_name("解文龙", ({ "xie wenlong","xie"}) );
       set("gender", "男性" );
       set("age", 40);
        set("long",
               "他就是独尊堡的少堡主。\n");
       set("combat_exp", 300500);
       set("attitude", "peaceful");
	   set("gin",800);
	   set("max_gin",800);
	   set("kee",800);
	   set("max_kee",800);
	   set("sen",800);
	   set("max_sen",800);
	   set("max_force",800);
	   set("force",800);
	   set_skill("unarmed",100);
	   set_skill("dodge",100);
	   set_skill("parry",100);
       set_skill("force",100);
       set("shili",([
         "name":"duzun_b",
         ]));
       setup();
 carry_object(__DIR__"obj/cloth")->wear();


}
