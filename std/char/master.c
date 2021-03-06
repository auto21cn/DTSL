// master.c last update from lanxin@jianghu 99-2-9

#include <dbase.h>
#include <login.h>
#include <ansi.h>


string time_period(int timep);

int prevent_learn(object me, string skill)
{
        mapping my_family, family;
        int betrayer, mylvl, lvl;

        lvl = this_object()->query_skill(skill, 1);
        mylvl = me->query_skill(skill, 1);
        if(betrayer = me->query("betrayer")) 
        {
                if(mylvl >= lvl - betrayer * 20) 
                {
                        message_vision("$N神色间似乎对$n不是十分信任，\n"
                                + "也许是想起$p从前背叛师门的事情\n"
                                + "...。\n", this_object(), me );
                        command("say 嗯 .... \n"
                                + "师父能教你的都教了，其他的你自己练吧。");
                        return 1;
                }
        }

        if(!me->is_apprentice_of(this_object())) 
        {
                if(!mapp(my_family = me->query("family"))) 
                        return 0;
                if(!mapp(family = this_object()->query("family"))) 
                        return 0;
                if((my_family["family_name"] == family["family_name"]))
                //&& (lvl <=  mylvl * 3 )) 
                {
                        command("hmm");
                        command("pat " + me->query("id"));
                        command("say 虽然你是我门下的弟子，可是并非我的嫡传弟子....");
                //      command("say 我只能教你这些粗浅的本门功夫，"
                //      + "其他的还是去找你师父学吧。");
                        command("say 还是去找你师父学吧。");
                        return 1;
                }
        }

        return 0;
}

int give_quest()
{
        int age, t, timep;
        mapping quest ;
        mixed *local;
        object me;
        string time_limit;

        me = this_player();

        // Let's see if this player is a ghost
        local = localtime(time() * 60);
        t = local[2] * 60 + local[1];       

        if((int)me->is_ghost())
        {
                write("鬼魂不可以讨要任务。\n");
                return 1;
        }

        if((string)me->query("family/master_name") != this_object()->name(1))
        {
                command("shake " + me->query("id"));
                command("say 还是去找你自己的师父要任务去吧。\n");
                return 1;
        }

        if((age = me->query("age")) > 16)
        {
                command("pat " + me->query("id"));
                command("say " + me->name(1) + "啊！过了十六后就别再向"
                        + "师父讨任务了，该自己去江湖厉练了。\n");
                return 1;
        }

        // Let's see if this player still carries an un-expired task
        if((quest =  me->query("quest")))
        {
                if(((int) me->query("task_time")) > time())
                {
                        command("say 还是先把你的任务完成了再说吧。\n");
                        return 1;
                } else
                        me->set("kee", me->query("kee") / 2 + 1);
                me->delete_temp("quest_number");
        }

        quest = QUEST_D("quest" + age)->query_quest();

        // each quest give 10 mins.
        timep = 600; 

        // A factor here to make time random
        timep = random(timep / 2) + timep / 2;

        //time_period(timep, me);
        time_limit = time_period(timep);

        if(quest["quest_type"] == "寻")
                command("say 给你" + time_limit + "去找来「" + quest["quest"]
                        + "」。");

        if(quest["quest_type"] == "杀")
                command("say 给你" + time_limit + "去杀了「" 
                        + quest["quest"] + "」。");

        me->set("quest", quest);
        me->set("task_time", (int)time() + (int)timep);

        if((int)me->query_temp("quest_number") < 5)
        me->add_temp("quest_number", 1);

        return 1;
}

string time_period(int timep)
{
        int t, d, h, m, s;
        string time;

        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if(d) time = chinese_number(d) + "天";
        else time = "";

        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";

        return time;
}

int accept_object(object who, object ob)
{
        int  exp, pot, score, val;
        string test;
        mapping quest;

        if(!(quest =  who->query("quest")))
                return 0;

        if((string)who->query("family/master_name") != this_object()->name(1))
        {
                command("say 还是去交给你自己的师父吧。");
                return 0;
        }

        if((string)ob->query("name") != quest["quest"] || ob->is_character())
        {
                command("shake " + who->query("id"));
                command("say 我可不想要这玩意。\n");
                return 0;
        }

        if((int)who->query("task_time") < time() )
        {
                command("sigh " + who->query("id"));
                command("say 可惜啊！" + who->name() + "，你没能"
                        + "在给定的时间内完成任务。\n");
                return 1;
        } else {
                command("smile " + who->query("id"));
                command("say 好样的！" + who->name()
                        + "，这件事你办得很好。\n");
                exp = quest["exp_bonus"]/2 + random(quest["exp_bonus"]/2)+1;

                // put a limit here
                if(exp > 150) exp = 150;
                exp = exp * (int) who->query_temp("quest_number");
                pot = exp / 5 + 1;

                //score = quest["score"]/2 + random(quest["score"]/2);
                who->add("combat_exp",exp);
                who->add("potential",pot);
                //who->add("score",score);

                tell_object(who,HIW"你被奖励了：\n" +
                chinese_number(exp) + "点实战经验\n"+
                chinese_number(pot) + "点潜能\n"NOR);
                //chinese_number(score)+"点综合评价\n"NOR);
                who->set("quest", 0);
                return 1;
        }
        return 1;
}

void give_rank(object ob) {}
