// steal.c

#include <ansi.h>

inherit F_CLEAN_UP;
int main(object me, string arg)
{
        string what, who;
        object ob, victim;
        int sp, dp;
        if( environment(me)->query("no_fight")||
            environment(me)->query("sleep_room")||
            environment(me)->query("no_steal") )
                return notify_fail("这里禁止行窃。\n");

        if( me->query_temp("ridee") )
          return notify_fail("你还骑在马上呢!\n");

        if( me->query_temp("stealing") )
                return notify_fail("你已经在找机会下手了！\n");

        if( !arg || sscanf(arg, "%s from %s", what, who)!=2 ) return
                notify_fail("指令格式：steal <物品> from <人物>\n");

        victim = present(who, environment(me));
        if( !victim || victim==me) return 
	notify_fail("你想行窃的对象不在这里。\n");
	if( userp(victim) && !living(victim))
	return notify_fail("你不能偷晕倒人身上的东西。\n");
if(userp(victim)&&victim->query("no_steal"))
return notify_fail("你现在不能偷他的东西\n");
	if( ! victim->is_character())
	return notify_fail("你可用ｇｅｔ　＜东西＞　ｆｒｏｍ　＜容器＞。\n");
	if( !wizardp(me) && wizardp(victim) )
                return notify_fail("你不能偷管理者身上的东西。\n");
	
        if( !ob = present(what, victim) ) {
                object *inv;
                inv = all_inventory(victim);
                if( !sizeof(inv) )
                        return notify_fail( victim->name() + 
"身上看起来没有什麽值钱的东西好偷。\n");
                inv=filter_array(inv,(:!$1->query("no_steal"):));
                inv=filter_array(inv,(:!$1->query("no_give"):));
                inv=filter_array(inv,(:!$1->query("nogive_player"):));
                if( !sizeof(inv) )
                        return notify_fail( victim->name() + 
"身上看起来没有什麽值钱的东西好偷。\n");
                ob = inv[random(sizeof(inv))];
        }
        if(ob->query("no_steal")||
        ob->query("no_give")||
        ob->query("nogive_player")
          )
        return notify_fail("那个东西不能偷！\n");
        sp =(int)me->query_kar() * (int)me->query_kar()/3;
        if( sp < 1 ) sp = 1;
        if( me->is_fighting() ) {
                sp /= 2;
                me->start_busy(3);
        }
        dp = (int)victim->query_dex() * (int)victim->query_dex()/5  + (int)ob->weight();
        if( victim->is_fighting() ) dp *= 10;
        if( ob->query("equipped") ) dp *= 10;

        write("\n你不动声色地慢慢靠近" + victim->name() + "，等待机会下手 
...\n\n");

        me->set_temp("stealing", 1);
        call_out( "compelete_steal", 3, me, victim, ob, sp, dp);

        return 1;
}

private void compelete_steal(object me, object victim, object ob, int sp, int 
dp)
{
  
  me->delete_temp("stealing");

	if(!victim){
  	tell_object(me, "太可惜了，你下手的目标已经不见了。\n");
    return;
  }
  if( environment(victim) != environment(me) ) {
  	tell_object(me, "太可惜了，你下手的目标已经走了。\n");
    return;
  }
	if((int)ob->query("no_get")) {
		tell_object(me,"你偷不到那个东西。\n");
		return;
	}
  if( (!living(victim) || (random(sp+dp) > dp) )
  		&&(random(me->query("combat_exp")+800000)>victim->query("combat_exp"))) {
  	if( !ob->move(me) ){
    	tell_object(me, "你摸到一" + ob->query("unit") + ob->name() 
                        + "，可是对你而言太重了，不得不放弃。\n");
      return;
    }
    tell_object(me, HIW "得手了！\n\n" NOR);
    tell_object(me, "你成功地偷到一" + ob->query("unit") + ob->name() + "！\n");
    if( living(victim) )
    	if( random(sp) > dp/2 )
      	message("vision", "你看到" + me->name() + "鬼鬼祟祟地从"
                         + victim->name() + "身上偷走了一" + ob->query("unit")
                         + ob->name() + "！\n", environment(me), ({me, victim }) );
				ob->do_steal(me);
  } 
  else{
  	if( random(sp) < dp/2 ) {
    	tell_object(me, victim->name() + "不经意地一转头，你急忙将手缩了回去！\n"
                      "还好，没有被发现。\n");
    	return;
    }
    tell_object(me, HIR "糟糕！你失手了！\n\n" NOR);
    message_vision("$N一回头，正好发现$n的手正抓著$P身上的" + ob->name() + "！\n\n"
                   + "$N喝道：「干什麽！」\n\n", victim, me);
    if( userp(victim) ) victim->fight_ob(me);
    else victim->kill_ob(me);
    me->fight_ob(victim);
    me->start_busy(5);
    me->add("thief", 1);
  }
}

int help(object me)
{
write(@HELP
指令格式 : steal <某物> from <某人>

这个指令让你有机会偷到他人身上的东西。成功了, 当然你就能获得
该样物品。可是, 马有失蹄, 人总有失风的时候, 当你失败时当然就
得付出代价, 至於是什麽代价......靠你自己去发掘罗。
HELP
    );
    return 1;
}
 
