inherit ITEM;
#include <ansi.h>

void create()
{
	set_name("药鼎",({"yao ding","ding"}) );
	set("long","这是一个药鼎，你可以用“合炼”(helian)来炼制药品。\n");
        set("no_get",1);
	set_weight(1000000);
	set("unit","个");
	set("value",100);
}

void init()
{
	add_action("do_helian","helian");
	
}
/*
string no_color(string arg)
{
      arg = replace_string(arg,  BLK, "");
	arg = replace_string(arg,  RED, "");
	arg = replace_string(arg,  GRN, "");
	arg = replace_string(arg,  YEL, "");
	arg = replace_string(arg,  BLU, "");
	arg = replace_string(arg,  MAG, "");
	arg = replace_string(arg,  CYN, "");
	arg = replace_string(arg,  WHT, "");
	arg = replace_string(arg,  HIR, "");
	arg = replace_string(arg,  HIG, "");
	arg = replace_string(arg,  HIY, "");
	arg = replace_string(arg,  HIB, "");
	arg = replace_string(arg,  HIM, "");
	arg = replace_string(arg,  HIC, "");
	arg = replace_string(arg,  HIW, "");
	arg = replace_string(arg,  NOR, "");
	arg = replace_string(arg,  BLINK, "");
	return arg;
}
*/
int do_helian(string arg)
{
object me = this_player();    
string met,met2,met3,met4,met5,name,iname,iname1,iname2,iname3,iname4,iname5,mname,mname1,mname2,mname3,mname4,mname5;
	object med,med2,med3,med4,med5,new_med;
	mapping heals,heals2,heals3,heals4,heals5;
	int lev;
	if(!arg||sscanf(arg,"%s %s %s %s %s %s",met,met2,met3,met4,met5,name)!=6)
		return notify_fail("请使用 helian 原料名字1 原料名字2 原料名字3 原料名字4 原料名字5 药的名字\n");
	if(!objectp(med=present(met,me))||!objectp(med2=present(met2,me))||!objectp(med3=present(met3,me))||!objectp(med4=present(met4,me))||!objectp(med5=present(met5,me)))
      return notify_fail("你身上没有这种原料!\n");
	if(me->query("vocation")!="药师")
		return notify_fail("你不是药师，不能炼制药!\n");
	if(!me->query("quest/final/yao"))
		return notify_fail("你没有在这里炼药的权利!\n");
	lev=(int)me->query_skill("bencao-shuli",1);
	if(lev<200)
	return notify_fail("你的本草术理太低了，怎么炼药？\n");
	if(me->query_int()<30)
	return notify_fail("你的悟性不够，无法炼药。\n");
	if(me->query("max_force")<2000)
		return notify_fail("你的内力不足以炼制药物!\n");
      // add by Yanyan. 限制每两天炼一次药。
      if(me->query("busy_time_lianyao",1)%2==0
      &&time()-me->query("busy_time_lianyao_time",1)<3600*24){//3600秒==1小时间隔
		return notify_fail("由于上一次炼制药物消耗了你大量的真元，你需要一段很长时间才能重新炼制。\n");
      }
      //add end.
	heals=med->query("heal");
	heals2=med2->query("heal");
	heals3=med3->query("heal");
	heals4=med4->query("heal");
	heals5=med5->query("heal");
     if(!heals||!heals2||!heals3||!heals4||!heals5) return notify_fail("这种东西不能用来炼药！\n");
     if(med->query("name")==med2->query("name")||
        med->query("name")==med3->query("name")||
        med->query("name")==med4->query("name")||
        med->query("name")==med5->query("name")||
        med2->query("name")==med3->query("name")||
        med2->query("name")==med4->query("name")||
        med2->query("name")==med5->query("name")||
        med3->query("name")==med4->query("name")||
        med3->query("name")==med5->query("name")||
        med4->query("name")==med5->query("name")) 
        return notify_fail("相同效果的药材放进去，效果就不好了！\n");
	if(me->is_busy())
		return notify_fail("你现在很忙，歇歇吧!\n");
	if(me->is_fighting())
		return notify_fail("你还是先打完仗再说吧！\n");
	name=replace_string(name,"$HIR$",""HIR"");
	name=replace_string(name,"$HIG$",""HIG"");
	name=replace_string(name,"$HIY$",""HIY"");
	name=replace_string(name,"$HIW$",""HIW"");
	name=replace_string(name,"$HIB$",""HIB"");
	name=replace_string(name,"$HIM$",""HIM"");
	name=replace_string(name,"$HIC$",""HIC"");
	name=replace_string(name,"$GRN$",""GRN"");
	name=replace_string(name,"$RED$",""RED"");
	name=replace_string(name,"$BLK$",""BLK"");
	name=replace_string(name,"$YEL$",""YEL"");
	name=replace_string(name,"$BLU$",""BLU"");
	name=replace_string(name,"$MAG$",""MAG"");
	name=replace_string(name,"$CYN$",""CYN"");
	name=replace_string(name,"$WHT$",""WHT"");
	name=name+NOR;
      new_med=new("/d/job/yishengjob/dan");
	new_med->set("name",name);
/*
  mname=no_color(new_med->query("name"));
  mname1=no_color(med->query("name"));
  mname2=no_color(med2->query("name"));
  mname3=no_color(med3->query("name"));
  mname4=no_color(med4->query("name"));
  mname5=no_color(med5->query("name"));
  iname=no_color(me->query("quest/final/yao/name"));
  iname1=no_color(me->query("quest/final/yao/med"));
  iname2=no_color(me->query("quest/final/yao/med2"));
  iname3=no_color(me->query("quest/final/yao/med3"));
  iname4=no_color(me->query("quest/final/yao/med4"));
  iname5=no_color(me->query("quest/final/yao/med5"));
*/  
  mname=new_med->query("name");
  mname1=med->query("name");
  mname2=med2->query("name");
  mname3=med3->query("name");
  mname4=med4->query("name");
  mname5=med5->query("name");
  iname=me->query("quest/final/yao/name");
  iname1=me->query("quest/final/yao/med");
  iname2=me->query("quest/final/yao/med2");
  iname3=me->query("quest/final/yao/med3");
  iname4=me->query("quest/final/yao/med4");
  iname5=me->query("quest/final/yao/med5");
  if(!me->query("quest/final/yao/done")&& mname==iname && mname1==iname1 && mname2==iname2 && mname3==iname3 && mname4==iname4 && mname5==iname5) 
{
me->add_skill("bencao-shuli",20);
me->add("potential",2000);
me->add("vocation_score",10000);
// me->delete("quest/final/yao/name");
me->set("quest/final/yao/done",1);
message("shout",HIY"〖"HIW"药师行会"HIY"〗"HIY"华佗(huatuo):" HIY+ me->query("name")+HIW"成功炼制独门秘药，故奖潜能二千点，职业声望一万点及本草术理二十级，！\n"NOR,users()); 
}


 if (mname1==iname1 && mname2==iname2 && mname3==iname3 && mname4==iname4 && mname5==iname5)
{
      message_vision("$N将"+mname1+"、"+mname2+"、"+mname3+"、"+mname4+"、"+mname5+"放进药鼎里，再徐徐注入自己的真源。\n\n"+name+"炼制好了！\n",me);
      destruct(med);
      destruct(med2);
      destruct(med3);
      destruct(med4);
      destruct(med5);
	new_med->move(me);
	me->add("vocation_score",200);
	me->add("vocation_exp",200);
// 	me->improve_skill("bencao-shuli",(lev/20+heals["heals"])/4);
	me->set("gin",0);
	me->set("kee",0);
	me->set("sen",0);
	me->set("force",0);
	me->add("max_force",-20);
	//add by Yanyan. 限制每两天炼一次药
	me->add("busy_time_lianyao",1);
	if(me->query("busy_time_lianyao",1)%2!=0)
	 me->set("busy_time_lianyao_time",time());
       //add end.
    return 1;
    
}
      destruct(med);
      destruct(med2);
      destruct(med3);
      destruct(med4);
      destruct(med5);
      destruct(new_med);
 return notify_fail("你用的药材或顺序不对,所以练出来的丹药成了废物。\n");
}

