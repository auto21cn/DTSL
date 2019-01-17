
inherit ITEM;
#include <ansi.h>


void create()
{
   set_name("罗汉塑像", ({ "luo han"}) );
   set_weight(5000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "铜");
     set("unit", "个");
     set("value",10000);
   }
   setup();
}

void init()
{
 // add_action("do_search","search");
 // add_action("do_mofang","mofang");
  add_action("do_jieyin","jieyin");
}

int is_get_of(object ob,object me)
{
  return notify_fail("这么沉的东西你也能搬起来？\n");
}

string long()
{
  object ob;
  ob=this_player();
  /*
  if(ob->query_temp("dtsl_quest_jzzy/step8")){
    ob->set_temp("dtsl_quest_jzzy/step9",1);
    ob->delete_temp("dtsl_quest_jzzy/step8");
    return "罗汉上有许多手印，似乎可以透过不同的手印，\n"+
           "贯通眉间轮、心轮和顶轮的三气。\n";}
  */
  //if(!ob->query_temp("dtsl_quest_jzzy/step1"))
  return "这是一尊罗汉的塑像。\n";
  /*
  ob->set_temp("dtsl_quest_jzzy/step2",1);
  ob->delete_temp("dtsl_quest_jzzy/step1");
  return "你来到罗汉座前，有若陷身由塑像布下的迷阵中，\n"+
         "那感觉实非任何言语可以形容万一。\n";
  */
}
/*
int do_search()
{
  object ob;
  object killer;
  
  ob=this_player();
  if(!ob->query_temp("dtsl_quest_jzzy/step2"))
  return 0;
  message_vision("$N四下搜查了一会，什么也没找到。\n",ob);
  if(random(ob->query("kar"))<5)
  return 1;
  ob->set_temp("dtsl_quest_jzzy/step3",1);
  ob->delete_temp("dtsl_quest_jzzy/step2");
  killer=new(__DIR__"killer");
  set_all_skill(killer,ob->query("max_pot")-90);
  copy_hp_item(ob,killer,"gin");
  copy_hp_item(ob,killer,"kee");
  copy_hp_item(ob,killer,"sen");
  killer->set("max_force",ob->query("max_force"));
  killer->set("force",ob->query("max_force"));
  tell_object(ob,BLU"你忽然觉得一阵冷风扑面而来！\n"NOR);
  tell_object(environment(ob),"\n突然跳出一个蒙面人来！！\n\n");
  killer->move(environment(ob));
  killer->kill_ob(ob);
  return 1;
}

int do_mofang(string arg)
{
 object ob;
 
  ob=this_player();
  if(!ob->query_temp("dtsl_quest_jzzy/step4"))
  return 0;
  if(!arg||(arg!="left"&&arg!="right"))
  return 0;
  if(arg=="left"){
  message_vision("$N卓立两尊塑像之间，首先摆出右边塑像的闲适姿势，\n"+
                 "接着又变换作右边怒目金刚的姿态，均维肖维妙，在\n"+
                 "殿外金黄的月色掩映下，加上堂畔微弱的灯火，几疑\n"+
                 "是$N忽然化身为护佛的罗汉，更似是其中一尊罗汉活\n"+
                 "了过来，那种感觉确是怪异无伦。\n",ob);
  ob->set_temp("mofang_left_ok",1);}
  if(arg=="right"){
  message_vision("$N举在头上的拳头倏地移后，拐个弯后，弓步击出，\n"+
                 "恰是怒目金刚旁那尊佛像的姿态，另一手却在身前画\n"+
                 "个似是毫无意义的圈子。\n",ob);
  ob->set_temp("mofang_right_ok",1);}
  if(ob->query_temp("mofang_right_ok")&&
     ob->query_temp("mofang_left_ok")){
     ob->set_temp("dtsl_quest_jzzy/step5",1);
     ob->delete_temp("dtsl_quest_jzzy/step4");
     ob->delete_temp("mofang_right_ok");
     ob->delete_temp("mofang_left_ok");}
  return 1;
}
*/

int do_jieyin(string arg)
{
   object ob;
   int flag2;
   int flag;
   
   ob=this_player();
   
   if(ob->query("gender")=="女性")
   return notify_fail("你什么也领悟不出来。\n");
   
   if(ob->query("dtsl_quest_jzzy_ok")){
    /*
    if(ob->query("gin")<100)
    return notify_fail("你觉得头脑昏沉，无法领会九字真言的诀窍。\n");
    if(ob->query("force")<20)
    return notify_fail("你的内力微弱，无法继续领会九字真言。\n");
    if(ob->is_busy()||ob->is_fighting())
    return notify_fail("你正忙者呢！\n");
    ob->receive_damage("gin",100);
    ob->add("force",-20);
    ob->improve_skill("jiuzi-zhenyan",ob->query_int()+random(ob->query_int()/3));
    ob->start_busy(random(2));
    message_vision("$N不自觉地他把两掌竖合，掌心微虚，如莲花之开放，\n"+
                  "接著两掌仰上相井，状如掬水，忽又化为两手反合十指\n"+
                  "相绞，变化出种种不同的手印。\n",ob);
   */
   return notify_fail("$N不自觉地他把两掌竖合，掌心微虚，如莲花之开放，\n"+
                      "接著两掌仰上相井，状如掬水，忽又化为两手反合十指\n"+
                      "相绞，变化出种种不同的手印。\n");
   return 1;}
   if(ob->query("perform_quest/jzzy_fail"))
   return notify_fail("你什么也领悟不出来。\n");
   
   if(!ob->query_temp("dtsl_quest_jzzy_action2"))
   return 0;
   if(ob->query("bellicosity")>100)
   return notify_fail("你觉得心绪烦乱，无法静下心来。\n");
   
   ob->delete_temp("dtsl_quest_jzzy_action2");
   message_vision("$N不自觉地他把两掌竖合，掌心微虚，如莲花之开放，\n"+
                  "接著两掌仰上相井，状如掬水，忽又化为两手反合十指\n"+
                  "相绞，变化出种种不同的手印。\n",ob);
   
   flag=ob->query_quest_kar();
   flag2=ob->query_kar();
   if(random(flag2)>29){
     tell_object(ob,"\n你从中领悟到了「九字真言」！\n");
     ob->set("dtsl_quest_jzzy_ok",1);
     ob->set_skill("jiuzi-zhenyan",10);
   }
   else{
     tell_object(ob,"你佛性不足，看来无法领悟「九字真言」了。\n");
     ob->add("perform_quest/jzzy_fail_times",1);
     if(ob->query("perform_quest/jzzy_fail_times")>=2){
     	ob->set("perform_quest/jzzy_fail",1);
     	tell_object(ob,"\n看来你永远也不能领悟这个绝技了。\n");
     }
  }
  // call_out("man_come",ob->query("kar"),ob);
   return 1;
}

/*
void man_come(object ob)
{
   object man,*inv;
   
   if(random(100)<90)
    return;
   
   inv=all_inventory(environment(ob));
   if(sizeof(inv)>1)
    return;
   
   if(!ob) return;
   if(base_name(environment(ob))!="/d/quest/jzzy/baodian")
   return;
   man=new(__DIR__"zhenyan-dashi");
   man->move(environment(ob));
   tell_object(environment(ob),"一个老僧人走了过来。\n");
   call_out("man_go",120,man);
   return;
}

void man_go(object ob)
{
  if(!ob) return;
  message_vision("$N缓步走开了。\n",ob);
  destruct(ob);
  return;
}
*/ 
