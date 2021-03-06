// kill.c

#include <ansi.h>
#include "valid_kill.h";
#include <org.h>

#define LOWER_LIMIT 2000
inherit F_CLEAN_UP;

string get_kill_msg(string arg)
{
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);	
	
	//arg = replace_string(arg, "$N", "$N"+CYN);
	//arg = replace_string(arg, "$n", "$n"+CYN);
	
	return arg+NOR;
	
}

int main(object me, string arg)
{
	object obj;
	string *killer, callname;
	string kill_msg;
	
	seteuid(getuid());
	
	if( !arg )
		return notify_fail("你想杀谁？\n");

	if(!objectp(obj = present(arg, environment(me))))
		return notify_fail("这里没有这个人。\n");
        if( (environment(me)->query("no_fight")||
	 environment(me)->query("sleep_room"))&&!obj->query("pker") )
		return notify_fail("这里不准战斗。\n");
        if( me->query_temp("ridee") )
          return notify_fail("你还骑在马上呢!\n");
        if(objectp(me->query_temp("city_war_guard")))
        return notify_fail("你正带兵打仗呢！\n");

	if( !obj->is_character() || obj->is_corpse() )
		return notify_fail("看清楚一点，那并不是活物。\n");

	if(obj==me)
		return notify_fail("用 suicide 指令会比较快:P。\n");
        
        if(objectp(obj->query_temp("city_war_guard")))
        return notify_fail("对方正带兵打仗呢！\n");
        
	if(stringp(obj->query("target_id"))&&obj->query("target_id")!=me->query("id"))
	return notify_fail(obj->name()+"根本不理会你的战斗请求。\n");
	if(arrayp(obj->query("target_id"))&&
	   member_array(me->query("id"),obj->query("target_id"))==-1)
	   return notify_fail(obj->name()+"根本不理会你的战斗请求。\n");
	
	if(userp(me)&&userp(obj)&&
	   me->query("shili/name")&&obj->query("shili/name")){
	  if(me->query("shili/name")==obj->query("shili/name"))
	   return notify_fail("同一帮会弟子不要互杀了！\n");
	  if(ORG_D->if_friend_org(me,obj))
	   return notify_fail("结盟帮会弟子间不能互杀！\n");
	}
	
	if(!valid_kill(me,obj)) return 0;
	callname = RANK_D->query_rude(obj);
	if(userp(obj)&&obj->query("age")<13)
        return notify_fail("这么小的玩家都杀，你太不讲江湖道义了！\n");
	if(userp(obj)&&me->query("age")<13)
        return notify_fail("你的武功这么低，还是不要杀人了！！\n");
	if(obj->query("accept_kill"))
		if(!obj->accept_kill(me,obj))
        	return (int)obj->accept_kill(me,obj);
	if( userp(obj))
   		log_file( "KILL_LOG", sprintf("(%s)%s tried to kill %s\n", ctime(time()), me->query("name"), obj->query("name")));
        
	if(stringp(me->query("env/kill_msg")))
         kill_msg = "\n"+me->query("env/kill_msg")+"\n\n";
	else kill_msg = "\n$N对著$n喝道：「" 
		+ callname + "！今日不是你死就是我活！」\n\n";
	
	message_vision(get_kill_msg(kill_msg),me,obj);

	me->kill_ob(obj);
	if( !userp(obj) )
		obj->kill_ob(me);
	else {
		obj->fight_ob(me);
		tell_object(obj, HIR "如果你要和" + me->name() 
			+ "性命相搏，请你也对这个人下一次 kill 指令。\n" NOR);
	}

	return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : kill <人物>
 
这个指令让你主动开始攻击一个人物，并且□试杀死对方，kill 和 fight 最大的
不同在於双方将会真刀实枪地打斗，也就是说，会真的受伤。由於 kill 只需单方
面一厢情愿就可以成立，因此你对任何人使用 kill 指令都会开始战斗，通常如果
对方是 NPC 的话，他们也会同样对你使用 kill。

其他相关指令: fight
HELP
    );
    return 1;
}
 
