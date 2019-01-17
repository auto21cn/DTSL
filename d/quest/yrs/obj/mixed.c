
inherit ITEM;
#include <ansi.h>
int do_paste(string arg);
void create()
{
        set_name(HIY"混合物"NOR, ({"mixed"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
    else  {
           set("unit", "块");
           set("yrs","mixed");
           set("long", "这是一块面粉和石蜡的混合物．\n");
        }
}

void init()
{
  add_action("do_paste","paste");
}

int do_paste(string arg)
{
  object ob;
  object target;
  string name;
  
  ob=this_player();
  if(!ob->query("dtsl_quest_yrs_ok"))
  return notify_fail("你把"+query("name")+"翻来覆去地看，看不出什么端倪.\n");
  if(!arg||sscanf(arg,"on %s",name)!=1)
  return notify_fail("你要把混合物粘到什么上面？\n");
  if(!objectp(target=present(name,ob)))
  return notify_fail("你身上没有这个东西！\n");
  if(target->query("yrs")!="skin")
  return notify_fail("混合物不能粘到"+target->name()+"上面去！\n");
  message_vision(YEL"$N小心翼翼地把"+query("name")+"粘到了"+target->name()+"上去。\n",ob);
  target->set("step1",1);
  destruct(this_object());
  return 1;
}