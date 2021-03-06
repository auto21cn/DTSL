// order.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
string *check_cmds=({
"sleep","suicide -f","suicide","quit","enroll","adopt","bai",
"exercise","repirate","learn","practice","study","remove",
"wield","wear","unwield","give","get","power","order","exert",
"perform"});

int main(object me, string arg)
{
	string dest, cmd;
	object ob;

	if( me != this_player(1) ) return 0;

	if( !arg || sscanf(arg, "%s to %s", dest, cmd) != 2 )
		return notify_fail("指令格式：order <某人> to <指令>\n");
	if( !(ob = present(dest, environment(me))) )
		return notify_fail("这里没有 " + dest + "　\n");
	if( !living(ob) )
		return notify_fail("这个物件不能执行命令　\n");
	if(!userp(ob))
	return notify_fail("你只能命令玩家。\n");
	if(!me->query("shili"))
	return notify_fail("你还是先加入一个帮会再使用这个命令吧！\n");
	if(me->query("shili/name")!=ob->query("shili/name"))
	return notify_fail("你们不是一个势力的，无法命令对方。\n");
	if(!me->query("shili/leader")&&ob->query("shili/power")&&
	me->query("shili/power")>=ob->query("shili/power"))
	return notify_fail("以你的权力无法命令对方。\n");
	if(ob->query("shili/leader"))
	return notify_fail("你想以下犯上吗？！\n");
	if(!me->query("shili/leader")&&ob->query("shili/wide")&&
	me->query("shili/wide")!=ob->query("shili/wide"))
	return notify_fail("你们不同属一个范围，无法命令对方！\n");
	if( wiz_level(ob) )
		return notify_fail("连巫师你也想命令，真是... ...　\n");
	if(!userp(ob))
	return notify_fail("你只能命令玩家。\n");
	if(sizeof(check_cmds)>sizeof(check_cmds-({cmd})))
	return notify_fail("这个指令禁止使用！\n");
	if(ob->is_busy())
	return notify_fail("对方正忙着呢！\n");
	if(ob->is_fighting())
	return notify_fail("等对方打完仗再说吧！\n");
	if( userp(ob) )
		log_file("FORCE_PLAYER_BANGHUI", sprintf("[%s] %s forces %s to %s\n",  
			ctime(time()), geteuid(me), geteuid(ob), cmd));
	return ob->force_me(cmd);
}

int help(object me)
{
	write(@Help
指令格式：order <某人> to <指令>

强迫某人做某事,但必须是一个帮会的，而且你们要属同一个地方
，同时你的等级比对方高。　
Help
	);
	return 1;
}
