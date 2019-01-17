
inherit NPC;
inherit F_BANKOWNER;
#include <ansi.h>
//#include <job_money.h>
void create()
{
        set_name("孙老板", ({"sun laoban", "sun"}));
        set("title", "钱庄掌柜");
        set("gender", "男性");
        set("age", 34);

        set("str", 22);
        set("int", 24);
        set("dex", 18);
        set("con", 18);

        set("kee", 500); 
        set("max_kee", 500);
        set("gin", 100);
        set("max_gin", 100);
        set("sen",300);
        set("max_sen",300);
        set("combat_exp",300000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("env/wimpy", 50);

        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 200);
		set_skill("cuff",120);
		set_skill("wuxing-quan",130);
        set("hand",({"wuxing-quan"}));
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 40);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
}

void init()
{
	add_action("do_check", ({"check", "chazhang", "查帐"}));
	add_action("do_convert", ({"convert", "duihuan", "兑换"}));
	add_action("do_deposit", ({"deposit", "cun", "存"}));
	add_action("do_withdraw", ({"withdraw", "qu", "取"}));
}

/*int accept_object(object me,object ob)
{
	int exp,sil,pot,i;
	object silver;
	i=0;
	if(me->query_temp("li_songxin_job"))
	if(!me->query_temp("li_songxin_job/1"))
		return notify_fail("你的信送错了地方！\n");
	if(!ob->query("li_songxin_job"))
		return notify_fail("你送的请柬不对啊！\n");
	me->delete_temp("li_job");
	me->delete_temp("li_songxin_job");
	me->delete_temp("dtsl_job");
	me->set_temp("busy_time",time());
        exp=me->query("max_pot")/4;
	pot=me->query("max_pot")/5;
	sil=LI_SONGXIN_JOB;
	me->add("combat_exp",exp);
	me->add("potential",pot);
	me->add("deposit",LI_SONGXIN_JOB);
	add_shili(me,exp/2,LI_SONGXIN_JOB/2);
	tell_object(me,"在这次行动中你增长了"+""HIW""+chinese_number(exp)+""NOR""+"点经验值"
                   +""HIW""+chinese_number(pot)+""NOR""+"点潜能\n");
	tell_object(me,"孙老板奖励了你"+""HIW""+chinese_number(sil)+""NOR""+"文铜钱\n");
	tell_object(me,"你钱庄的存款增加了！\n");
	return 1;
}
*/