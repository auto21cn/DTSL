
#include <ansi.h>
#include <condition.h>
#include <job_money.h>

inherit F_CLEAN_UP;

string *killer_name=({"赵","钱","孙","李","周","吴","郑","王"});
string *killer_id=({"一","二","三","四","五","六","七","八"});

int update_condition(object ob, int times)
{
   object target;
   string name;
   
   if(ob->query_temp("liyuan_job/step")!=13)
  return 0;
   
   if(times<=0){
   	tell_object(ob,HIB"\n你忽然觉得一阵冷风袭来！\n\n"NOR);
   	name=killer_name[random(sizeof(killer_name))]+
       killer_id[random(sizeof(killer_id))];
       
       target=new("/d/job/liyuanjob/killer5");
  target->set("combat_exp",ob->query("combat_exp"));
  set_all_skill(target,ob->query("max_pot")-70);
  copy_hp_item(ob,target,"gin");
  copy_hp_item(ob,target,"kee");
  copy_hp_item(ob,target,"sen");
  target->set("max_force",ob->query("max_force"));
  target->set("force",ob->query("max_force"));
  target->set("target_id",ob->query("id"));
  target->set("name",name);
  target->set("target_id",ob->query("id"));
  target->move(environment(ob));
  tell_object(ob,"忽然跳出一名蒙面男子!!\n");
  message_vision("\n$N对$n叫到：遇见我算你倒霉，留下银两还可以考虑你的小命！\n",
                 target,ob);
  target->kill_ob(ob);
       	
   	return 0;}
   	   
      ob->apply_condition("liyuan_job_killer2", times - 1);
   if( times < 1 ) return 0;
   return CND_CONTINUE;
}
