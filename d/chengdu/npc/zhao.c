//普通的npc
inherit NPC;
#include <ansi.h>

void create()
{
       set_name("赵天远", ({ "zhao tianyuan","zhao","tian","yuan"}) );
       set("gender", "男性" );
       set("age", 48);
       set("long",
               "他就是成都的知府赵天远。\n");
       set("combat_exp", 52500);
       set("attitude", "friendly");
       
       setup();
 carry_object(__DIR__"obj/guanfu")->wear();


}
