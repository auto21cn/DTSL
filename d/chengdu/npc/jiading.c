//普通的npc
inherit NPC;
#include <ansi.h>

void create()
{
       set_name("家丁", ({ "jia ding","jia","ding"}) );
       set("gender", "男性" );
       set("age", 28);
       set("long",
               "这是李财主家的家丁。\n");
       set("combat_exp", 52500);
       set("attitude", "friendly");
       
       setup();
 carry_object(__DIR__"obj/cloth")->wear();


}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
	 

	if (!ob || !present(ob, environment())) return;
	switch( random(2) ) {
		case 0:
			say( "家丁说道：这位" + RANK_D->query_respect(ob)
          + "没事情可不要乱往里面走!\n");
			break;
		case 1:
			say( "家丁上上下下打量了你几眼。\n");
			break;
	}

}
