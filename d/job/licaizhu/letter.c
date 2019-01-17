
 
inherit ITEM;
#include <ansi.h>

int do_give(string arg);
void create()
{
   set_name(HIY"请柬"NOR, ({"qing jian","qing","jian"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一封结婚的请柬。\n");
                set("unit", "封");
                set("no_sell",1);
                set("no_drop",1);
                set("no_give",1);
               
        }
}

void init()
{
  add_action("do_give","song");
}

int do_give(string arg)
{
  object ob,target;
  int sil;
  
  ob=this_player();
  if(!arg)
  return notify_fail("你要把请柬送给谁？\n");
  if(!ob->query_temp("li_song_job"))
  return 0;
  if(!objectp(target=present(arg,environment(ob))))
  return notify_fail("这里没有这个人！\n");
  if(!userp(target))
  return notify_fail("这个东西只能给玩家！\n");
  if(query("target_id")!=target->query("id"))
  return notify_fail("你送错对象了！\n");
  
  sil=100+ob->query("max_pot")-random(5);
  ob->add("deposit",sil);
  ob->delete_temp("li_song_job");
  ob->delete_temp("dtsl_job");
  ob->set("busy_time",time());
  tell_object(ob,"你打开请柬，从中拿出"+MONEY_D->money_str(sil)+",揣进怀中。\n");
  tell_object(ob,"你的钱庄存款增加了！\n");
  destruct(this_object());
  return 1;
}