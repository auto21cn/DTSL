
inherit "/std/guard.c";

void create()
{
   set_name("少帅军",({ "bing" }) );
   set("gender", "男性" );
   set("age", 32);
   set("long", "这是彭梁的少帅军。\n");
   set("guard","pengliang");   
   set("combat_exp",800000);
   set("attitude", "peaceful");
   
   set_this_skills("middle");
   set_all_skill(this_object(),160);
   
   setup();
   
}

