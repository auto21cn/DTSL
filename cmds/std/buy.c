// buy.c

inherit F_CLEAN_UP;

#define EVENT_D "/obj/event.c"

int buy_object(object me,object owner, string item);
int main(object me, string arg)
{
	string item, targ;
	object ob, owner;
	int price, afford;
	object* inv;

    if( this_player()->is_busy() )
			return notify_fail("你现在正忙着呢。\n");

	if( !arg || sscanf(arg, "%s from %s", item, targ)!=2 )
		return notify_fail("指令格式：buy <某物> from <某人>\n");

	if( !objectp(owner = present(targ, environment(me))) )
		return notify_fail("你要跟谁买东西？\n");

	if( userp(owner) ) {
		message_vision("$N想向$n购买「" + item + "」。\n", me, owner);
	        notify_fail("对方好像不愿意跟你交易。\n");
		return 1;
	}
        if(owner->do_buy(item)) return 1;
	price=buy_object(me,owner,item);
	if( price < 1 ) return 0;
        switch(MONEY_D->player_pay(me, price)){
        	
		case 0: return notify_fail("你身上带的钱不够啊!\n");
		case 2: return notify_fail("您的零钱不够了，银票又没人找得开。\n");
		}
        me->start_busy(1);
	return (int)owner->complete_trade(me, item);

}
int buy_object(object me, object owner,string what)
{
   string ob;
   object vendor;
   int i;
   int trade_skill;

   if( stringp(ob = owner->query("vendor_goods/" + what)) ){
     vendor=new(ob);
     i=ob->query("value");
     
     i=EVENT_D->get_trade_value(ob,i);
     trade_skill = me->query_skill("trade",1);
     if(trade_skill>300)
     	trade_skill = 300;
     
     i=i-i*trade_skill/(1200);
     if(i<=0) i=5;
     destruct(vendor);
     return i;}
   else
     return 0;
}
int help(object me)
{
   write( @HELP
指令格式: buy <something> from <someone>

这一指令让你可以从某些人身上买到物品。
HELP
   );
   return 1;
}
