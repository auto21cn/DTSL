
inherit NPC;
#include <ansi.h>
string *strong=({BLU"不堪一击"NOR,BLU"还算结实"NOR,HIB"比较结实"NOR,GRN"非常结实"NOR,
GRN"坚固异常"NOR,HIG"坚不可摧"NOR,HIR"无可匹敌"NOR,});

string *damage=({BLU"寻常兵刃"NOR,BLU"微具伤害"NOR,HIB"颇具伤害"NOR,CYN"轻微威力"NOR,
CYN"巨大威力"NOR,HIC"非同凡响"NOR,HIC"不同凡响"NOR,GRN"无与伦比"NOR,GRN"无可匹敌"NOR,
HIG"神乎其神"NOR,HIG"世间罕见"NOR,HIW"举世无双"NOR,HIW"惊世骇俗"NOR,HIR"武林至宝"NOR,});
int do_jianding(string arg);
string show_damage();
string show_strong();
void create()
{
   set_name("尚剑师",({ "shang jianshi","shang"}) );
        set("gender", "男性" );
        set("age", 32);
        set("str",30);
        set("jiali",200);
        set("max_gin",1000);
        set("max_sen",1000);
        set("max_kee",1000);
        set("max_force",1000);
        set("force",1000);
        create_family("东溟派",5,"剑师");
        set("inquiry",([
            "伤害":(:show_damage:),
            "坚强度":(:show_strong:),
            ]));
    setup();
   //carry_object("/obj/cloth/mandongming3")->wear();
  
}
void init()
{
  object ob;
  add_action("do_jianding","jianding");
  ob=this_player();
  if(ob&&!ob->is_busy()&&!ob->is_fighting()){
   remove_call_out("welcome");
   call_out("welcome",1,ob);}
  
}

void welcome(object ob)
{
   if(!ob) return;
   switch(random(3)){
     
     case 0: message_vision("$N朝$n笑道：你可以向我询问“伤害”来得知目前伤害的描述。\n",
             this_object(),ob);
             break;
     case 1: message_vision("$N朝$n笑道：你可以向我询问“坚强度”来得知目前伤害的描述。\n",
             this_object(),ob);
             break;
     case 2: message_vision("$N朝$n笑道：你可以使用“jianding”来鉴定你的兵器。\n",
             this_object(),ob);
             break;}
  return;
}

string get_strong(object weapon)
{
  int sto;
  sto=weapon->query("strong");
  if(sto>300) sto=300;
  return strong[sto/50];
}

string get_damage(object weapon)
{
  int dam;
  dam=weapon->query("weapon_prop/damage");
  dam+=weapon->query("user_skill")/2;
  if(weapon->query("super"))
  dam+=weapon->query("super")*weapon->query("super");
  if(dam>13*50) dam=13*50;
  return damage[dam/50];
}
  

int do_jianding(string arg)
{
  object ob,weapon;
  string str1,str2;
  ob=this_player();
  if(!arg)
  return notify_fail("剑师奇道：你要找我鉴定什么？\n");
  if(arg==ob->query("id")){
  message_vision("$N冲$n神秘地一笑：我看你智商也就是个白痴，武艺也就是个废物！呵呵。\n",this_object(),ob);
  return 1;}
  if(!objectp(weapon=present(arg,ob)))
  return notify_fail("剑师仔细看了看：你身上没有这个东西啊？\n");
  if(!weapon->query("skill_type"))
  return notify_fail("剑师笑笑：对不起，我只鉴定武器的。\n");
  if(weapon->query("super")>4)
  return notify_fail("剑师一摆手：这么好的兵器还用我鉴定吗？\n");
  str1=get_strong(weapon);
  str2=get_damage(weapon);
  message_vision("$N用手指轻轻弹了弹"+weapon->name()+":看其坚强度，约是"+str1+"吧！\n",this_object());
  message_vision("$N挥舞了几下"+weapon->name()+":看其伤害力，约是"+str2+"吧！\n",this_object());
  return 1;
}

string show_damage()
{
   string msg;
   int i;
   
   msg="";
   for(i=0;i<sizeof(damage);i++)
    msg +=damage[i]+"\n";
   
  this_player()->start_more(msg);
  return "这就是目前伤害力的各种描述，你好好看看吧！\n";
}

string show_strong()
{
   string msg;
   int i;
   
   msg="";
   for(i=0;i<sizeof(strong);i++)
    msg +=strong[i]+"\n";
   
  this_player()->start_more(msg);
  return "这就是目前坚强度的各种描述，你好好看看吧！\n";
}
   