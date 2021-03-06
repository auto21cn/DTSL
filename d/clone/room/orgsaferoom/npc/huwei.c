

inherit NPC;

#include <ansi.h>

void create()
{
   set_name("护卫",({ "hu wei","hu","wei","orgsafe_guard" }) );
   set("gender", "男性" );
   set("age",35);
   set("long", "这是一名护卫。\n");
       
   set("combat_exp",600000);
   set_skill("dodge",150);
   set_skill("parry",150);
   set_skill("force",150);
   set_skill("finger",150);
   set_skill("dujie-zhi",150);
   set_skill("literate",150);
   set_skill("tianmo-dafa",150);
   set_skill("tianmo-jue",150);
   set_skill("tianmo-huanzong",150);
   
   set("max_gin",2000);
   set("max_kee",2000);
   set("max_sen",2000);
   set("force",2000);
   set("max_force",2000);
   set("perform_quest/liudao",1);
   set_temp("apply/damage",100+random(100));
   set_temp("apply/armor",100+random(100));
   set_temp("apply/dodge",100+random(100));
   
   setup();
  
}

void die()
{
   object ob;
   
   ob=query_temp("last_damage_from");
   if(!ob) return ::die();
   if(stringp(environment(this_object())->query("shili/name")))
    set("shili/name",environment(this_object())->query("shili/name"));
   
   command("banghui 我被"+HIR+ob->name()+"杀死了！各位兄弟小心了！");
   command("chat* die "+query("id"));
   
   return ::die();
   
}