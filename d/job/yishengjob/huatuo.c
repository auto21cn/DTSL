inherit NPC;
#include <ansi.h>
int item_player();
mapping yaoname2=([
RED"金银花"NOR:"jinyinhua",
YEL"川乌"NOR:"chuanwu",
HIY"冰片"NOR:"bingpian",
GRN"天冬"NOR:"tiandong",
HIC"血竭"NOR:"xuejie",
BLU"大黄"NOR:"dahuang",
MAG"巴豆"NOR:"badou",
]);

mapping yaoname3=([
RED"茯苓"NOR:"fuling",
YEL"灵芝"NOR:"lingzhi",
HIY"没药"NOR:"moyao",
GRN"地龙"NOR:"dilong",
HIC"归尾"NOR:"guiwei",
BLU"黄柏"NOR:"huangpo",
MAG"琥珀"NOR:"hupo",
]);

mapping yaoname4=([
RED"鹤顶红"NOR:"hedinghong",
YEL"紫花"NOR:"zihua",
HIY"甘草"NOR:"gancao",
GRN"菖蒲"NOR:"changpu",
HIC"九子"NOR:"jiuzi",
BLU"兰花"NOR:"lanhua",
MAG"附子"NOR:"fuzi",
]);

mapping yaoname5=([
RED"鹿茸"NOR:"lurong",
YEL"牛黄"NOR:"niuhuang",
HIY"熊胆"NOR:"xiongdan",
GRN"蟾酥"NOR:"zhansu",
HIC"蛤粉"NOR:"xiafen",
BLU"虎骨"NOR:"hugu",
MAG"穿山甲壳"NOR:"chuanshanjiake",
]);

mapping yaoname=([
RED"红花"NOR:"honghua",
YEL"陈皮"NOR:"chenpi",
HIY"人参"NOR:"renshen",
GRN"当归"NOR:"danggui",
HIC"雪莲"NOR:"xuelian",
BLU"生地"NOR:"shengdi",
MAG"何首乌"NOR:"heshouwu",
]);

mapping itemname=([
RED"天王保命丹"NOR:"dan",
HIM"九转还魂丹"NOR:"dan",
HIW"贯气通脉丹"NOR:"dan",
MAG"三才封髓丹"NOR:"dan",
BLU"七宝美髯丹"NOR:"dan",
]);

void create()
{
  set_name("华佗", ({"huatuo"}));
  set("age", 60);
  set("gender", "男性");
  set("long", "当今最强的药师，你可以问他有关“药师”职业的问题。\n");
  set("attitude", "peaceful");
  set("str", 50);
  set("per", 10);
  set("combat_exp", 1200000);
  set("max_kee", 1500);
  set("max_sen", 1500);
  set("max_force", 1500);
  set("force", 1500);
  set("force_factor", 150);
  set_skill("unarmed", 90);
  set_skill("dodge", 60);
  set_skill("parry", 60);
  set_skill("force", 80);
 set("inquiry", ([
        "药师":   (: item_player:),
      ]));
  setup();

}
int item_player()
{
  object me = this_object();
  object who = this_player();
  object yaofang;
  string *itemn;
  int itemz;
  string *n,*n2,*n3,*n4,*n5;
  int z;
  int z2;
  int z3;
  int z4;
  int z5;
  if(who->query("vocation") != "药师"){
	   	
		command("kok");
		command(
		  "say 你还是先去把自己变成药师吧！\n");
		return 1;
	    }
  if (who->query("quest/final/yao"))
  {
    message_vision ("$N对$n说道：我不是已经把药方给你了吗？\n",me,who);
    return 1;
 } 
 

  n=keys(yaoname);
  z=random(sizeof(n));  

  n2=keys(yaoname2);
  z2=random(sizeof(n2));  
  n3=keys(yaoname3);
  z3=random(sizeof(n3));  
  n4=keys(yaoname4);
  z4=random(sizeof(n4));  
  n5=keys(yaoname5);
  z5=random(sizeof(n5));  
  itemn=keys(itemname);
  itemz=random(sizeof(itemn));  
//  itemid1=itemname[itemn[itemz]];
  who->set("quest/final/yao/name", itemn[itemz]);
  who->set("quest/final/yao/med", n[z]);
  who->set("quest/final/yao/med2", n2[z2]);
  who->set("quest/final/yao/med3", n3[z3]);
  who->set("quest/final/yao/med4", n4[z4]);
  who->set("quest/final/yao/med5", n5[z5]);
  yaofang=new("/d/job/yishengjob/yaofang");
  yaofang->move(who);
  message_vision ("这里有一张药方，你找到上面写的药材后拿去合炼吧,记得要按顺序!\n",me,who);
  return 1;
}

