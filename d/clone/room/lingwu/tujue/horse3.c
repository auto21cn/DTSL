
inherit NPC;
#include <ansi.h>
void create()
{
   set_name(HIW"白马"NOR,({ "horse"}) );
        set("race", "野兽" );
     set("long", "这是一匹木制的白马。\n");
     set("verbs",({"hoof"}));
	 set("limbs",({"头","腿","肚子"}));
  setup();

}
void clear(object ob)
{
  ob->delete_temp("kill_horse1");
  ob->delete_temp("kill_horse2");
  ob->delete_temp("kill_horse3");
  return;
}
void noway(object ob)
{
  message_vision(HIR"只听木马内部机关响了几声，木马突然迅捷地朝$N踢去，正中$N的腹部！"NOR,ob);
  clear(ob);
  ob->unconcious();
  return;
}
void die()
{
  object ob;
  ob=query_temp("last_damage_from");
  if(!ob) return ::die();
  if(!ob->query_temp("kill_horse1"))
   ob->set_temp("kill_horse1","白马");
  else if(!ob->query_temp("kill_horse2"))
   ob->set_temp("kill_horse2","白马");
  else if(!ob->query_temp("kill_horse3")){
   
   ob->set_temp("kill_horse3","白马");
   if(ob->query("kar")<=15){
   	if(ob->query_temp("kill_horse1")!="蓝马"||
           ob->query_temp("kill_horse2")!="红马"||
           ob->query_temp("kill_horse3")!="白马"){
            noway(ob);return ::die();}}
   else
   if(ob->query("kar")<=20){
   	if(ob->query_temp("kill_horse1")!="红马"||
           ob->query_temp("kill_horse2")!="蓝马"||
           ob->query_temp("kill_horse3")!="白马"){
            noway(ob);return ::die();}}
   else
   if(ob->query("kar")<=25){
   	if(ob->query_temp("kill_horse1")!="白马"||
           ob->query_temp("kill_horse2")!="红马"||
           ob->query_temp("kill_horse3")!="蓝马"){
            noway(ob);return ::die();}}
   else
   if(ob->query("kar")<=30){
   	if(ob->query_temp("kill_horse1")!="红马"||
           ob->query_temp("kill_horse2")!="白马"||
           ob->query_temp("kill_horse3")!="蓝马"){
            noway(ob);return ::die();}}
   clear(ob);
   tell_object(ob,HIG"只听墙上喀嚓几声响后，显现出一个黑洞来！\n"NOR);
   ob->set("super_force_tujue_no_horse",1);
  environment(ob)->set("exits/enter",__DIR__"tujue");
  call_out("del_enter",5,environment(ob));
  return ::die();}
  return ::die();
}

void del_enter(object ob)
{
  ob->delete("exits/enter");
  remove_call_out("del_enter");
}