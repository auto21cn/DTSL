
#include <ansi.h>
#include <job_money.h>
inherit ITEM;

int do_find();

void create()
{
        set_name("招安令", ({ "paper" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long", "");
                set("no_give",1);
                set("no_drop",1);
                set("no_sell",1);
                set("value", 300);
                set("material", "wood");
        }

        setup();
}

string long()
{
  return "\n"+
  "※※※※※※※※※※※※※※※※\n"+
  "  这是一张招安令，上面写着  \n"+
  "　　　　　　　　　　　　　　\n"+
  "　　　　  招安侠客          \n"+
  ""+"         "+query("target_name")+"      \n"+
  "          居住在　　　　　　\n"+
  ""+"         "+query("target_place")+"      \n"+
  "※※※※※※※※※※※※※※※※\n";
}

void init()
{
  add_action("do_find","soucha");
}
int do_find()
{
  object ob;string here;
  object killer;
  
  ob=this_player();
  if(!ob->query_temp("liyuan_job/step"))
  return notify_fail("你看了看四周，发现侠客好象不是藏在这里。\n");
  here=base_name(environment(ob));
  if(here!=query("target_where"))
  return notify_fail("你看了看四周，发现侠客好象不是居住在此处。\n");
  killer=new(__DIR__"man1");
  killer->set("combat_exp",ob->query("combat_exp"));
  set_all_skill(killer,ob->query("max_pot")-100);
  copy_hp_item(ob,killer,"gin");
  copy_hp_item(ob,killer,"kee");
  copy_hp_item(ob,killer,"sen");
  killer->set("max_force",ob->query("max_force"));
  killer->set("force",ob->query("max_force"));
  killer->set("target_id",ob->query("id"));
  killer->set("env/wimpy",30);
  killer->set("name",query("target_name"));
  killer->set("long","据说此人本领高强，长安李阀已经派"+ob->query("name")+"来招安他了。\n");
  killer->set_temp("apply/armor",50+random(50));
  killer->move(environment(ob));
  message_vision("$N慢慢走了过来。\n",killer);
  message_vision("\n$N赶紧将招安令递给了$n！\n",ob,killer);
  message_vision("$N看了看招安令，笑道：想让我为李阀效力，可要问我的拳头答不答应！\n",killer);
  destruct(this_object());
  return 1;
}
