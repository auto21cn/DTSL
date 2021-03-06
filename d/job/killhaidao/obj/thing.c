#include <ansi.h>
#include <job_money.h>
inherit ITEM;
mapping name=([
HIY"九转灵珠"NOR:"jiuzhuan lingzhu",HIW"夜明珠"NOR:"yeming zhu",HIG"翡翠项链"NOR:"necklace",HIW"白玉白虎"NOR:"tigger",
HIY"金娃娃"NOR:"jin wawa",HIC"避水珠"NOR:"bishui zhu",HIG"翡翠珊瑚"NOR:"shan hu",HIW"白玉美人"NOR:"baiyu meiren",
HIC"夜光手镯"NOR:"shou zhuo",HIY"金砖"NOR:"jin zhuan",HIW"白玉萧"NOR:"xiao",HIG"猫眼"NOR:"mao yan",HIG"玛瑙"NOR:"ma nao",
HIG"琴谱"NOR:"qin pu",HIY"金项圈"NOR:"xiang quan",HIY"钻石"NOR:"zuan shi",HIW"天山雪莲"NOR:"xue lian",HIW"千年人参"NOR:"ren shen",
]);
#include "want_owner.h"

int do_give(string arg);
int do_name(string arg);
int do_hecheng(string arg);
void create()
{
   string *n;int i;
   string *w;
   
   n=keys(name);
   i=random(sizeof(n));
   set_name(n[i],({name[n[i]]}));
   set_weight(5000);
   
   if( clonep() )
     set_default_object(__FILE__);
   else {
  
     set("no_sell",1);
     set("no_give",1);
     set("no_drop",1);
     set("unit", "个");
     set("value", 0);
     set("baowu",1);
     
   }
   setup();
   
}
string *part=({"left","right","up","down","center"});
string to_part(string arg)
{
   switch(arg){
   case "left":return "左边";
   case "right":return "右边";
   case "up":return "上边";
   case "down":return "下边";
   case "center":return "中间";}
}
string long()
{
  
  string *w;
  int i;
  if(query("long")) return query("long");
  if(random(100)>60){
    w=keys(want_owner);
    i=random(sizeof(w));
    set("want_owner",want_owner[w[i]]);
    set("long","据说这是"+w[i]+"一直想要的宝物。\n");}
  else 
  if(random(100)==38){
  	set_name(YEL"羊皮"NOR,({"yang pi","pi"}));
  	i=random(sizeof(part));
  	set("part",part[i]);
  	set("quest",1);
  	set("long","看起来这是一幅羊皮做的图的"+to_part(part[i])+"部分。\n");}
  else
  set("long","这个一个罕见的宝物。\n");
  return query("long");
}

void init()
{
  if(!query("last_time"))
   set("last_time",time());
  add_action("do_give","xianbao");
  add_action("do_name","want");
  add_action("do_hecheng","hecheng");
  if(userp(environment(this_object())))
  	set("no_get",1);
  
}

int clean_up()
{
  if(time()-query("last_time")<300)
   return 0;
  return 1;
}


string *weaponclass=({
"blade","sword","spear","fork","staff","hammer","axe","dagger","whip"});
string to_weapon(string arg)
{
  switch(arg){
  
  case "blade":return "刀类";
  case "sword":return "剑类";
  case "spear":return "枪类";
  case "fork":return "叉类";
  case "staff":return "杖类";
  case "hammer":return "锤类";
  case "axe":return "斧类";
  case "dagger":return "匕首类";
  case "whip":return "鞭类";}
}
//maybe give money or exp or pot or weapon.
int do_give(string arg)
{
   object ob;
   object target;
   int money,pot,exp;
   string name,target_name;
   string weapon;
  
   ob=this_player();
   if(!query("want_owner")) return 0;
   if(!arg||sscanf(arg,"%s %s",target_name,name)!=2)
   return notify_fail("你要献给谁什么宝物？\n");
   if(!objectp(target=present(target_name,environment(ob))))
   return notify_fail("这里没有这个人！\n");
   if(!present(name,ob))
   return notify_fail("你身上没有这个东西！\n");
   if(present(name,ob)->query("want_owner")!=base_name(target))
   return notify_fail(target->name()+"一摇头：这个东西我可不想要！\n");
   if(present(name,ob)->query("give_weapon")==base_name(target))
   return notify_fail(target->name()+"说道：你到底想要什么名字的兵器？\n");
   message_vision("$N朝$n笑道：谢谢帮我找到这么珍贵的东西！\n",target,ob);
   
   if(ob->query_temp("dm_job_find")){
   ob->delete_temp("dm_job_find");
   ob->delete_temp("dm_job_find_where");
   ob->delete_temp("have_killer");
   ob->delete_temp("dtsl_job");}
  
   switch(random(4)){
   case 0:
   money=ob->query("max_pot")*2*100;
   ob->add("deposit",money);
   tell_object(ob,target->name()+"给了你"+MONEY_D->money_str(money)+"。\n");
   add_shili(ob,1,money/500);
   break;
   case 1:
   pot=150+random(50);
   ob->add("potential",pot);
   tell_object(ob,target->name()+"奖励了你"+HIY+chinese_number(pot)+"点潜能。\n");
   break;
   case 2:
   exp=260+random(40);
   ob->add("combat_exp",exp);
   tell_object(ob,target->name()+"奖励了你"+HIY+chinese_number(exp)+"点经验。\n");
   add_shili(ob,exp/10,1);
   break;
   case 3:
   weapon=weaponclass[random(sizeof(weaponclass))];
   ob->set_temp("will_get_weapon/owner",base_name(target));
   ob->set_temp("will_get_weapon/weapon",weapon);
   present(name,ob)->set("give_weapon",base_name(target));
   tell_object(ob,target->name()+"决定给你一件"+to_weapon(weapon)+"的兵器，请使用\n"+
               "want id 兵器名字 with 宝物名字 来索取兵器（兵器名字支持颜色字符）。\n");
   return 1;
   break;}
   destruct(present(name,ob));
   return 1;
}

int do_name(string arg)
{
   object ob;
   object target;
   string wp,target_name,name;
   object new_weapon;
   
   ob=this_player();
   if(!ob->query_temp("will_get_weapon"))
   return 0;
   if(!arg||sscanf(arg,"%s %s with %s",target_name,wp,name)!=3)
   return notify_fail("请使用want id 兵器名字 with 宝物名字 来要兵器。\n");
   if(!objectp(target=present(target_name,environment(ob))))
   return notify_fail("这里没有这个人！\n");
   if(!present(name,ob))
   return notify_fail("你身上没有这个东西！\n");
   if(present(name,ob)->query("want_owner")!=base_name(target))
   return notify_fail("你好象拿错东西了。\n");
   if(ob->query_temp("will_get_weapon/owner")!=base_name(target))
   return notify_fail("你好象认错人了吧？？\n");
        wp=replace_string(wp,"$HIR$",""HIR"");
	wp=replace_string(wp,"$HIG$",""HIG"");
	wp=replace_string(wp,"$HIY$",""HIY"");
	wp=replace_string(wp,"$HIW$",""HIW"");
	wp=replace_string(wp,"$HIB$",""HIB"");
	wp=replace_string(wp,"$HIM$",""HIM"");
	wp=replace_string(wp,"$HIC$",""HIC"");
	wp=replace_string(wp,"$GRN$",""GRN"");
	wp=replace_string(wp,"$RED$",""RED"");
	wp=replace_string(wp,"$BLK$",""BLK"");
	wp=replace_string(wp,"$YEL$",""YEL"");
	wp=replace_string(wp,"$BLU$",""BLU"");
	wp=replace_string(wp,"$MAG$",""MAG"");
	wp=replace_string(wp,"$CYN$",""CYN"");
	wp=replace_string(wp,"$WHT$",""WHT"");
	wp=wp+NOR;
   
   new_weapon=new(__DIR__"weapon/"+ob->query_temp("will_get_weapon/weapon"));
   new_weapon->set("name",wp);
   new_weapon->set("weapon_prop/damage",random(ob->query("max_pot")));
   new_weapon->set("max_strong",random(ob->query("max_pot")));
   new_weapon->set("strong",new_weapon->query("max_strong"));
   new_weapon->move(ob);
   tell_object(ob,target->name()+"给了你一"+new_weapon->query("unit")+
               new_weapon->query("name")+"。\n");
   ob->delete_temp("will_get_weapon");
   destruct(present(name,ob));
   return 1;
}


int do_hecheng(string arg)
{
   object ob;
   object part1,part2,part3,part4,part5;
   string p1,p2,p3,p4,p5;
   string *content;
   int i;
   object baowu;
   
   ob=this_player();
   if(!arg||sscanf(arg,"%s and %s and %s and %s and %s",
    p1,p2,p3,p4,p5)!=5)
   return notify_fail("你要合成什么？\n");
   if(!objectp(part1=present(p1,ob)))
   return notify_fail("你身上没有"+p1+"。\n");
   if(!objectp(part2=present(p2,ob)))
   return notify_fail("你身上没有"+p2+"。\n");
   if(!objectp(part3=present(p3,ob)))
   return notify_fail("你身上没有"+p3+"。\n");
   if(!objectp(part4=present(p4,ob)))
   return notify_fail("你身上没有"+p4+"。\n");
   if(!objectp(part5=present(p5,ob)))
   return notify_fail("你身上没有"+p5+"。\n");
   if(!part1->query("quest")||!part2->query("quest")||
   !part3->query("quest")||!part4->query("quest")||
   !part5->query("quest")||!query("quest"))
   return notify_fail("这些东西不能合成在一起。\n");
   content=({"left","right","up","down","center"});

     if(member_array(part1->query("part"),content)==-1)
      return notify_fail("这些东西不能合成在一起。\n");
      content=content-({part1->query("part")});
     if(member_array(part2->query("part"),content)==-1)
      return notify_fail("这些东西不能合成在一起。\n");
      content=content-({part2->query("part")});
     if(member_array(part3->query("part"),content)==-1)
      return notify_fail("这些东西不能合成在一起。\n");
      content=content-({part3->query("part")});
     if(member_array(part4->query("part"),content)==-1)
      return notify_fail("这些东西不能合成在一起。\n");
      content=content-({part4->query("part")});
     if(member_array(part5->query("part"),content)==-1)
      return notify_fail("这些东西不能合成在一起。\n");
      content=content-({part5->query("part")});
   tell_object(ob,"你将这几个羊皮小心地拼凑了起来。\n");
   baowu=new(__DIR__"map");
   baowu->move(ob);
   if(part1!=this_object())
   destruct(part1);
   if(part2!=this_object())
   destruct(part2);
   if(part3!=this_object())
   destruct(part3);
   if(part4!=this_object())
   destruct(part4);
   if(part5!=this_object())
   destruct(part5);
   destruct(this_object());
   return 1;
}