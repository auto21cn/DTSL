// kill.c

#include <ansi.h>
#include "valid_kill.h";
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string *killer, callname;
	object *t;
	int i;

	if( environment(me)->query("no_fight") )
		return notify_fail("这里不准战斗。\n");

	if( !arg )
		return notify_fail("你想杀谁？\n");

	if(!objectp(obj = present(arg, environment(me))))
		return notify_fail("这里没有这个人。\n");
	
	if(objectp(me->query_temp("city_war_guard")))
        return notify_fail("你正带兵打仗呢！\n");

	if( !obj->is_character() || obj->is_corpse() )
		return notify_fail("看清楚一点，那并不是活物。\n");

	if(obj==me)
		return notify_fail("用 suicide 指令会比较快:P。\n");
	
	if(objectp(obj->query_temp("city_war_guard")))
        return notify_fail("对方正带兵打仗呢！\n");

	callname = RANK_D->query_rude(obj);
        t = me->query_team();
	if(sizeof(t) <=1)
	return notify_fail("你现在并没有参加任何队伍或队伍只你一个人。(use kill)\n");
	
	if(userp(obj)&&obj->query("age")<13)
        return notify_fail("这么小的玩家都杀，你太不讲江湖道义了！\n");
        if(userp(obj)&&me->query("age")<13)
        return notify_fail("你的武功这么低，还是不要杀人了！！\n");
        if(obj->query("accept_kill"))
          if(!obj->accept_kill(me,obj))
           return (int)obj->accept_kill(me,obj);
       
       if(stringp(obj->query("target_id"))&&obj->query("target_id")!=me->query("id"))
	return notify_fail(obj->name()+"根本不理会你的战斗请求。\n");
	if(arrayp(obj->query("target_id"))&&
	   member_array(me->query("id"),obj->query("target_id"))==-1)
	   return notify_fail(obj->name()+"根本不理会你的战斗请求。\n");
        if(!valid_kill(me,obj)) return 0;
        
	if( userp(obj))
   log_file( "KILL_LOG", sprintf("(%s)
%s tried to kill with team %s\n", ctime(time()), me->query("name"), obj->query("name")));
	/*if( userp(obj) )
		return notify_fail("唉！你可不可以改掉以众欺寡的恶习？\n");*/
	for(i=0;i<sizeof(t);i++)
	if( t[i])
	if( environment(me) != environment(t[i]))
		return notify_fail("队员不都在场。(use kill)\n");		
	message_vision("\n$N对著$n喝道：「" 
		+ callname + "！今日不是你死就是我们活！」\n\n", me, obj);
        for(i=0;i<sizeof(t);i++)
	{
	if(t[i]){
		
		if(stringp(obj->query("target_id"))&&obj->query("target_id")!=t[i]->query("id"))
	        continue;
	        
	        if(objectp(t[i]->query_temp("city_war_guard")))
                continue;
                
	        if(arrayp(obj->query("target_id"))&&
	   member_array(t[i]->query("id"),obj->query("target_id"))==-1)
	   continue;
        if(!valid_kill(t[i],obj)) continue;
        if(t[i]->query("age")<13) continue;
        if( userp(obj))
   log_file( "KILL_LOG", sprintf("(%s)
%s tried to kill %s\n", ctime(time()), t[i]->query("name"), obj->query("name")));

                t[i]->set_temp("ttarget",obj->query("id"));
		t[i]->kill_ob(obj);
		if(!userp(obj))
		 obj->kill_ob(t[i]);
		else
		 obj->fight_ob(t[i]);
		}
	}
	return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : teamkill <人物>
 
这个指令让你的队伍主动攻击一个人物．
其他相关指令: team,fight,kill

HELP
    );
    return 1;
}
 
