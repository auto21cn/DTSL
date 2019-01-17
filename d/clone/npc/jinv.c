#include <ansi.h>
inherit NPC;

int do_kiss(string arg);
int do_sleep(string arg);

mapping *npcnames=({
([
"name":"春风",
"id1":"chun",
"id2":"feng",
]),	
([
"name":"小月",
"id1":"xiao",
"id2":"yue",
]),
([
"name":"百花",
"id1":"bai",
"id2":"hua",
]),
([
"name":"如月",
"id1":"ru",
"id2":"yue",
]),
([
"name":"翠灵",
"id1":"cui",
"id2":"ling",
]),
	
	
	
});

void create()
{
   mapping names;
   
   names = npcnames[random(sizeof(npcnames))];
   
   set_name(names["name"],({ names["id1"]+" "+names["id2"],names["id1"],names["id2"] }) );
   set("gender", "女性" );
   set("age", 22);
   set("long", "这是一名风尘女子。\n");
       
   set("combat_exp", 5000);
   set("str", 10);
   set("per", 28);
   set("attitude", "friendly");
   set("chat_chance",10);
   set("chat_msg",({
    query("name")+"微微笑道：有钱的大爷，可以亲亲（qin "+names["id1"]+"）我啊！\n",
    query("name")+"笑道：有钱的大爷，我可以和你睡觉（shuijiao "+names["id1"]+"）的！\n",
   }));

   setup();
   
  
}

void init()
{
  add_action("do_kiss","qin");
  add_action("do_sleep","shuijiao");
}

int do_kiss(string arg)
{
  object me,ob;string str;
  int money;
  
  me=this_player();
  ob=this_object();
  money = 0;
  
  if(!arg)
  return notify_fail("你趴在地上，舔了"+query("name")+"的脚一下。\n");
  if(!objectp(ob=present(arg,environment(me))))
  return notify_fail("恩，有这个人吗？！\n");
  if(ob!=this_object())
  return notify_fail(query("name")+"喊道：嘿，你干什么呢？！\n");
  if(me->query("gender")=="女性")
  return notify_fail(query("name")+"一笑：你找错对象了！\n");
  if(me->query("gin")<200)
  return notify_fail(query("name")+"笑道：看你样子，没什么精神，等会吧！\n");
  if(me->is_busy())
  return notify_fail(query("name")+"一笑：你还是歇歇吧，真是贪心啊！\n");
  if(me->is_fighting())
  return notify_fail(query("name")+"往旁边一闪：你还是先打仗吧！\n");
  if(me->query_per()<10){
  	message_vision("$N朝$n一皱眉：你长得好恶心啊，钱可得算多点！\n",ob,me);
  	money += 5000;
  	
  }
  if(me->query_per()<20){
  	message_vision("$N朝$n微微一皱眉：看你相貌，钱可得算多点！\n",ob,me);
  	money += 4000;
  	
  }	
  if(me->query_per()<26){
  	message_vision("$N朝$n微微一笑："+RANK_D->query_respect(me)+",你好坏啊！钱少算点吧！\n",ob,me);
  	money += 3000;
  	
  }
  if(me->query_per()<31){
  	message_vision("$N脸上微微一红，朝$n嗔道："+RANK_D->query_respect(me)+",你坏，你坏！\n",ob,me);
  	money += 2000;
  }
  else{
  	message_vision("$N一脸红晕，羞答答地对$n说：能认识"+RANK_D->query_respect(me)+"这样的人，是我的福气。\n",ob,me);
  	money += 1000;
  } 
  switch(MONEY_D->player_pay(me, money)){
  	case 0:
  	case 2:
  		message_vision("$N朝$n骂道，你亲我一次得拿出来"+MONEY_D->money_str(money)+"，老娘银票不收的！\n",ob,me);
  		command("heng "+me->query("id"));
  		return 1;
  }	
  message_vision("\n$N侧过身来，$n在$N的脸上亲了一口。\n",ob,me);
  me->add("gin",-200);
  me->start_busy(2);
  return 1;
}

int do_sleep(string arg)
{
  object me,ob;string str;
  int money;
  
  me=this_player();
  ob=this_object();
  money = 0;
  
  if(!arg)
  return notify_fail("你趴在地上，舔了"+query("name")+"的脚一下。\n");
  if(!objectp(ob=present(arg,environment(me))))
  return notify_fail("恩，有这个人吗？！\n");
  if(ob!=this_object())
  return notify_fail(query("name")+"喊道：嘿，你干什么呢？！\n");
  if(me->query("gender")=="女性")
  return notify_fail(query("name")+"一笑：你找错对象了！\n");
  if(me->query("gin")<200||me->query("kee")<200)
  return notify_fail(query("name")+"笑道：看你样子，没什么精神，等会吧！\n");
  if(me->is_busy())
  return notify_fail(query("name")+"一笑：你还是歇歇吧，真是贪心啊！\n");
  if(me->is_fighting())
  return notify_fail(query("name")+"往旁边一闪：你还是先打仗吧！\n");
  if(me->query_per()<10){
  	message_vision("$N朝$n一皱眉：你长得好恶心啊，钱可得算多点！\n",ob,me);
  	money += 50000;
  	
  }
  if(me->query_per()<20){
  	message_vision("$N朝$n微微一皱眉：看你相貌，钱可得算多点！\n",ob,me);
  	money += 40000;
  	
  }	
  if(me->query_per()<26){
  	message_vision("$N朝$n微微一笑："+RANK_D->query_respect(me)+",你好坏啊！钱少算点吧！\n",ob,me);
  	money += 30000;
  	
  }
  if(me->query_per()<31){
  	message_vision("$N脸上微微一红，朝$n嗔道："+RANK_D->query_respect(me)+",你坏，你坏！\n",ob,me);
  	money += 20000;
  }
  else{
  	message_vision("$N一脸红晕，羞答答地对$n说：能认识"+RANK_D->query_respect(me)+"这样的人，是我的福气。\n",ob,me);
  	money += 10000;
  }
  switch(MONEY_D->player_pay(me, money)){
  	case 0:
  	case 2:
  		message_vision("$N朝$n骂道，和我睡一次得拿出来"+MONEY_D->money_str(money)+"，老娘银票不收的！\n",ob,me);
  		command("heng "+me->query("id"));
  		return 1;
  }
  message_vision(CYN"$n拥抱着$N，给了$N一个深深的吻！\n"+
                "$N依偎在$n的怀里，眼中含情脉脉，脸上娇羞无限．\n"NOR,me,ob);
  call_out("step2",2,me,ob);
        return 1;
}

int step2(object me, object who)
{
        if(me->query("gender") == "男性" ) 
            message_vision(YEL"$N紧紧地抱住$n，两个人的心在一起跳动，感情在一起升温！！\n"NOR,me,who);
        else
            message_vision(YEL"$N紧紧地抱住$n，两个人的心在一起跳动，感情在一起升温！！\n"NOR,who,me);

        call_out("remove_cloth",1,me);
        call_out("remove_cloth",1,who);
        call_out("step3",3,me,who);
        return 1;
}

int step3(object me, object who)
{
        message_vision(MAG"$N和$n沉浸在幸福的海洋里＃＠＃％＆＆＊＆％￥＃\n"NOR,me,who);
        call_out("step4",2,me,who);
        return 1;
}

int step4(object me, object who)
{
        if(me->query_condition("xxx"))
                me->clear_condition("xxx");
        if(who->query_condition("xxx"))
                who->clear_condition("xxx");

        me->receive_damage("gin",me->query("max_gin")/2);
        me->receive_damage("kee",me->query("max_kee")/2);

        who->receive_damage("gin",who->query("max_gin")/2);
        who->receive_damage("kee",who->query("max_kee")/2);
       message_vision(HIW"终于一切又恢复了平静．\n"NOR,me,who);
       
        return 1;
}

int remove_cloth(object me)
{
        object *inv;
        string str;
        int i;
        // remove all staff before sleepping :P
        inv = all_inventory(me);
        for(i=0; i < sizeof(inv); i++ ) {
            if( inv[i]->query("equipped") == "worn" ) {
                if( inv[i]->unequip() ) {
                    if( !stringp(str = inv[i]->query("remove_msg")) )
                        switch(inv[i]->query("armor_type")) {
                                case "cloth":
                                case "armor":
                                case "surcoat":
                                case "boots":
                                        str = YEL "$N将$n脱了下来。\n" NOR;
                                        break;
                                case "bandage":
                                        str = YEL "$N将$n从伤口处拆了下来。\n" NOR;
                                        break;
                                default:
                                        str = YEL "$N卸除$n的装备。\n" NOR;
                        }
                message_vision(str, me, inv[i]);
                }
            } else if ( inv[i]->query("equipped") == "wielded" ) {
                if(inv[i]->unequip() ) {
                    if( !stringp(str = inv[i]->query("unwield_msg") )) 
                        str = YEL "$N放下手中的$n。\n" NOR;
                message_vision(str, me, inv[i]);
                }
            }
        }
}
