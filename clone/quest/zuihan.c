#include <ansi.h>

inherit NPC;

void create()
{
   set_name("醉汉",({ "zui han","zui","han"}) );
        set("gender", "男性" );
        set("age", 32);
   set("long", "这是一个喝多了的醉汉，浑身散发着一股酒气。\n");
       
   set("combat_exp",500000);
   
   
   setup();
   
   add_money("gold",10);
  
}

void die()
{
   object ob;
   int pot;
   
   ob=query_temp("last_damage_from");
   if(!ob) return ::die();
   
   pot=200+random(100);
   ob->add("potential",pot);
   
   tell_object(ob,"你得到了"+HIY+chinese_number(pot)+NOR+"点潜能！\n");
   
   return ::die();
   
}