// throwing.c

#include <ansi.h>;
inherit F_CLEAN_UP;
inherit F_COMMAND;
inherit F_DBASE;

int do_throw(object me, object ob, object victim);

private int throw_result(object me, object victim, object ob);

int main(object me, string arg)
{
        string what, who, skill; 
        object ob, victim;

        seteuid(geteuid(me));

        if( !arg
        ||      sscanf(arg, "%s at %s", what, who)!=2)
                return notify_fail("命令格式: throw <物品> at <某人>。\n");

        ob = present(what, me);
        if( !ob) return notify_fail("你要扔什么？\n");

        if (ob->query("no_drop"))
                return notify_fail("这个东西不能离开你。\n");
        if (ob->query("embedded"))
                return notify_fail("这个东西现在取不下来。\n");

        if (!(victim = present(who, environment(me))))
                return notify_fail("这里没有你的目标。\n");

        if (!victim)
                return notify_fail("这里并无此人！\n");

        if (!living(victim))
                return notify_fail("这不是活物！\n");

        if (victim->query("winner"))
                return notify_fail("不可对"+victim->short()+"放肆！\n");
        
        if(stringp(victim->query("target_id"))&&victim->query("target_id")!=me->query("id"))
	return notify_fail(victim->name()+"根本不理会你的战斗请求。\n");
	
	if(arrayp(victim->query("target_id"))&&
	   member_array(me->query("id"),victim->query("target_id"))==-1)
	   return notify_fail(victim->name()+"根本不理会你的战斗请求。\n");

        if (me->is_busy() )
                return notify_fail("你前一个动作还没有做完。\n");

        if (victim == me) 
                return notify_fail("何必多此一举？\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("在这里不能攻击他人。\n");

        if( !wizardp(me) && wizardp(victim) )
                return notify_fail("你正要有所动作，突然天空一道闪电把你劈倒，一个声音道：不准对巫师大人不敬！\n");
        
        if(me->query("pker"))
	return notify_fail("通缉犯还是老实地呆会吧！\n");
	
	if(userp(me) && userp(victim)&&me->query("age")<13)
	return notify_fail("你年龄这么小，还是老实一下吧！\n");
	
	if(userp(me) && userp(victim)&&me->query("combat_exp")<300000)
	return notify_fail("你经验这么低，还是老实一下吧！\n");
                
        if ( userp(me) && userp(victim) && victim->query("age") < 13 )
                return notify_fail("你的心肠太黑了, 对手无缚鸡之力的玩家也下得了手。\n");
        if ( userp(me) && userp(victim) && victim->query("combat_exp") < 15000 )
                return notify_fail("你的心肠太黑了, 对手无缚鸡之力的玩家也下得了手。\n");

        if( ob->query("weapon_prop") && me->is_exert() &&
            ob == me->query_temp("weapon"))
                 return notify_fail("你正在使用"+me->query_exert()+"，无法扔出"+ob->name()+"。\n");
        if( ob->query("weapon_prop") && me->is_perform() &&
            ob == me->query_temp("weapon"))
                 return notify_fail("你正在使用"+me->query_perform()+"，无法扔出"+ob->name()+"。\n");
                 
        return do_throw(me, ob, victim);
}

int do_throw(object me, object ob, object victim)
{
        string msg;

        if( !stringp(msg = ob->query("throw_msg"))&&!me->query_skill("throwing",1) )
             msg = "\n$N手一扬，将"+ob->name()+"对准$n掷了过去！\n";
        else
             msg="\n$N施展出阴癸派暗器绝学，手一抖，将"+ob->name()+"对准$n掷了过去！\n";
        message_vision(msg, me, victim);

        me->start_busy(1);

        throw_result(me, victim, ob);

        return 1;
}

private int throw_result(object me, object victim, object ob)
{
        string *limbs, str, dodge_skill, result,*dodges;
        int ap, dp;mapping action;
        int damage;
        object ob2;
        
        damage=0;
        ap = me->query_str()*me->query_int();
        dp = victim->query_cor()*victim->query_int();
        ap *= me->query("combat_exp")/1000;
        
        dp *= victim->query("combat_exp")/1000;
        ap = random(ap);
        ap +=me->query_skill("throwing",1)/2;
        
        damage=me->query_skill("throwing",1);
        
        victim->add_temp("offenders/"+me->query("id"), 1);

        if ( ap > dp/2){
                limbs = victim->query("limbs");
victim->receive_wound("kee", damage+me->query_str()*damage/30, me);
 victim->receive_damage("kee",(ob->query_weight()/500)+me->query_str()+damage, me);
                
                if(ob->query("throwing")){
                     message_vision(CYN"结果只听$N"+CYN+"一声惨叫，"+ob->name()+CYN+"已然插在$N"+CYN+"的"+limbs[random(sizeof(limbs))]+"上。\n"NOR, victim);
                              if(ob->query_amount()>1){
                                 ob->set_amount(ob->query_amount()-1);
                                 ob->set("victim", victim->query("id"));
                                 ob2=new(base_name(ob));
                                 if ((int)ob2->query_amount()>1)
                                 ob2->set_amount(1);
                                 ob2->move(victim);}
                               else{
                                  ob->set("victim", victim->query("id"));
                                  ob->move(victim);}
                                // if(stringp(ob->query("poison"))) victim->apply_condition(ob->query("poison"), ob->query("damage")*2);
                                 victim->receive_wound("kee", me->query_str()*ob->query("weapon_prop/damage"), me);
                                 victim->kill_ob(me);
                }
                else {  
                     message_vision(CYN"$N猝不及防，$n"+CYN+"砸在了$N的"+limbs[random(sizeof(limbs))]+"上。\n"NOR, victim, ob);
                     if(ob->query_amount()>1){
                                 ob->set_amount(ob->query_amount()-1);
                                 ob->set("victim", victim->query("id"));
                                 ob2=new(base_name(ob));
                                 if ((int)ob2->query_amount()>1)
                                 ob2->set_amount(1);
                                 ob2->move(environment(me));}
                               else{
                                  ob->set("victim", victim->query("id"));
                                  ob->move(environment(me));}
                     if (!userp(victim) && victim->query_temp("offenders/"+me->query("id")) > 1)
                        victim->kill_ob(me);
                     else{
                        victim->fight_ob(me);
                        call_out("do_respond", 1, victim, me);
                        }
                }
                me->start_busy(random(3));                

result = COMBAT_D->eff_status_msg((int)victim->query("kee") * 100/(int)victim->query("max_kee"));
        message_vision("($N"+result+")\n", victim);
        }

        else if ( ap < dp/7 && ob->query_weight() < 7000 
                && victim->query("race") == "人类"){
                message_vision(CYN"不料$N眼明手快，身子一侧，把$n"+CYN+"轻轻地接在手里。\n\n"NOR, victim, ob);
                me->start_busy(random(3));
                if(ob->query_amount()>1){
                                 ob->set_amount(ob->query_amount()-1);
                                 ob->set("victim", victim->query("id"));
                                 ob2=new(base_name(ob));
                                 if ((int)ob2->query_amount()>1)
                                 ob2->set_amount(1);
                                 ob2->move(victim);}
                               else{
                                  ob->set("victim", victim->query("id"));
                                  ob->move(victim);}
                if (!userp(victim) && victim->query_temp("offenders/"+me->query("id")) > 1)
                        victim->kill_ob(me);
                else
                call_out("e_mote", 1, victim, me);      
        }

        else {

                dodges=victim->query("dodge");
			    if(sizeof(dodges)==0) dodge_skill = "dodge";
				else dodge_skill=dodges[random(sizeof(dodges))];
                action = SKILL_D(dodge_skill)->query_action(victim);
				str=action["action"];
                message_vision(str+"\n", me, victim);
                me->start_busy(random(3));
                if(ob->query_amount()>1){
                                 ob->set_amount(ob->query_amount()-1);
                                 ob->set("victim", victim->query("id"));
                                 ob2=new(base_name(ob));
                                 if ((int)ob2->query_amount()>1)
                                 ob2->set_amount(1);
                                 ob2->move(environment(me));}
                               else{
                                  ob->set("victim", victim->query("id"));
                                  ob->move(environment(me));}
                
                if (!userp(victim) && victim->query_temp("offenders/"+me->query("id")) > 1)
                        victim->kill_ob(me);
                else
                call_out("do_respond", 1, victim, me);
        }

        return 1;
}


void e_mote(object victim, object me)
{
        int i;
        string *emote = ({
        "sneer", "callname", "consider", "killair", "grin",
        "nonsense", "walkby", "cut", "chicken", "kick", });

        if (!me || environment(me) != environment(victim))
        return;

        i = random(sizeof(emote));

        EMOTE_D->do_emote(victim, emote[i], me->query("id"));
}
        
void do_respond(object victim, object me)
{
        string att; 

        if (!me || !victim || environment(me) != environment(victim))
        return;

        att = victim->query("attitude");

        if (victim->query("shen") < 0)
                return victim->kill_ob(me);

        if (att == "friendly" && victim->query("race") == "人类")
                return e_mote(victim, me);
        
        if (att == "heroism" || att == "aggressive")
                return victim->kill_ob(me);     

        if (att == "peaceful" && random(5)== 1) 
                return victim->kill_ob(me);

        else if(victim->query("race") == "人类")
        EMOTE_D->do_emote(victim, "brag", me->query("id"));

        return victim->fight_ob(me);    
}

