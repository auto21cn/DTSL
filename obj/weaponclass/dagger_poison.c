
#include <weapon.h>

inherit DAGGER;

void create()
{
	set_name("匕首", ({ "dagger" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("material", "steel");
	}
	init_dagger(4,20,20);

	set("wield_msg", "$N从怀中摸出一把$n握在手中。\n");
	set("unwield_msg", "$N将手中的$n藏入怀中。\n");
	setup();
}

void init()
{
  add_action("do_sandu","sandu");
  add_action("do_zha","zha");
}

int do_sandu(string arg)
{
   object ob,target;
   string msg;
   
   ob=this_player();
   
   if(!arg)
   return notify_fail("你要给谁散毒？\n");
   if(!objectp(target=present(arg,environment(ob))))
   return notify_fail("这里没有这个人。\n");
   if(ob->query("vocation")!="药师")
   return notify_fail("只有药师能给人散毒。\n");
   if(ob->query_skill("bencao-shuli",1)<60)
   return notify_fail("你的本草术理太低了，无法给对方散毒！\n");
   if(ob==target)
   return notify_fail("你不能给自己散毒。\n");
   if(!target->query("env/sandu"))
   return notify_fail("对方现在不允许别人给他散毒！\n");
   if(!target->query("liandu_times")&&!target->query("dazao_poison"))
   return notify_fail("对方现在身体很好，没必要散毒。\n");
   
   msg="$N拿起"+query("name")+"，在$n的手腕上割了一个口子，只见一股绿色的毒汁流了出来。\n";
   msg+="$n大叫一声，状似疯癫，几乎昏死过去！！\n\n";
   target->set("gin",0);
   target->set("kee",0);
   target->set("sen",0);
   target->set("liandu_times",0);
   
   if(target->query("dazao_poison")){
     if(ob->query_skill("bencao-shuli",1)<target->query("dazao_poison")-100)
       message_vision("$n中的毒非常厉害，以$N的本草术理还无法散毒！\n",target,ob);
     else
     target->set("dazao_poison",0);
   }
   
   msg+="只见"+query("name")+"瞬间已成了黑色，$N连忙扔掉了"+query("name")+"！\n";
   
   message_vision(msg,ob,target);
   
   destruct(this_object());
   return 1;  
}

int do_zha(string arg)
{
   object ob,target;
   string msg;
   int dlev;
   
   ob=this_player();
   
   if(!arg)
   return notify_fail("你要扎谁？\n");
   if(!objectp(target=present(arg,environment(ob))))
   return notify_fail("这里没有这个人。\n");
   if(ob->query("vocation")!="药师")
   return notify_fail("只有药师能使用"+query("name")+"。\n");
   if(ob->query_skill("poison",1)<60)
   return notify_fail("你的毒术太低了，无法使用"+query("name")+"！\n");
   if(ob==target)
   return notify_fail("你不能扎自己。\n");
   
   if(target->query("vocation")!="铁匠")
   return notify_fail("对方不是铁匠！\n");
   
   if(target->query("vocation_degree")>=3)
   return notify_fail("一个人潜能有限，使用毒药无法在激发"+target->name()+"的潜能了。\n");
   
   if(target->query("dazao_poison"))
   return notify_fail("对方已经身中剧毒，无法激发潜能！\n");
   
   msg="$N拿起"+query("name")+"，猛地朝$n的手臂扎去！\n";
   msg+="$n大叫一声，但双目却充满了精神，浑身似乎有了无穷的精力！\n\n";  
   target->add("vocation_degree",1);
   target->save();
   msg+="只见"+query("name")+"瞬间已成了黑色，$N连忙扔掉了"+query("name")+"！\n";
   
   message_vision(msg,ob,target);
   if(ob->query_skill("poison",1)>=400)
    dlev=ob->query_skill("poison",1)-100;
   else
    dlev=ob->query_skill("poison",1)/3;
   target->set_temp("duanzao_skills",dlev);
   target->set("dazao_poison",ob->query_skill("poison",1));
   destruct(this_object());
   return 1;  
}
   