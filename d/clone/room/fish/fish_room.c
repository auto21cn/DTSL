// 钓鱼.c 

inherit ROOM; 

#include <ansi.h>

#define DEBUG 1

void create() 
{ 
set("short",HIY"钓"HIR"鱼"HIW"台"NOR); 
set("long", @LONG 
你走进这里，哇，有好多的人在这里钓鱼呀！不时的传来兴奋的喊
叫声，这肯定又是有谁钓到了大鱼，看到他们忙忙碌碌、兴奋的样子，
你还有什么值得犹豫的，赶快拿好你的鱼杠开始钓鱼(diao)吧？ 
LONG ); 

set("exits", ([ 
"down" : __DIR__"room", 
]));

set("objects",([
 __DIR__"yufu":1,
 ]));
 
set("no_fight", 1); 
set("no_clean_up", 0); 

setup(); 

} 
void init() 
{ 
add_action("do_fish", "fish"); 
add_action("do_fish", "diao"); 
} 

int do_fish(string arg) 
{ 

object me; 
me = this_player(); 

if (me->query("combat_exp") >100000&&!DEBUG) { 
message_vision(HIG"天上一道闷雷一下子击中了$N！\n" + 
HIR "一个声音对着$N大喝：别想捣乱，经验这么高了还来钓鱼，你该不是想欺负新手吧！\n\n\n"NOR,me); 
me->move("/d/yangzhou/hotel"); 
return 1; 
} 
if (me->query("age") >13&&!DEBUG) { 
message_vision(HIG"天上一道闷雷一下子击中了$N！\n" + 
HIR "一个声音对着$N大喝：这是儿童游乐场所,你只能在一旁看着！\n\n\n"NOR,me); 
me->move("/d/yangzhou/hotel"); 
return 1; 
} 

if ( !arg || ( arg != "yu" ) ) 
return notify_fail("你要钓什么啊?\n");  


if(!me->query_temp("apply/yugan"))
return notify_fail("不拿渔杆怎么钓鱼啊？\n");

if (me->query("kee") < 20 ) 
return notify_fail("你快支持不住了，先歇会儿吧！\n"); 


if (me->is_busy()) 
return notify_fail ("你正忙着呢！\n"); 

if(me->query_temp("is_fishing"))
return notify_fail("注意看鱼漂，一心不能二用。\n");

me->set_temp("is_fishing",1);

message_vision("$N拿着一把钓鱼杆坐在大石头上钓起鱼来……。\n", me); 

call_out("do_fishing",8+random(7),me);

return 1;

}

void do_fishing(object me)
{
  object fish;
  
  if(!me) return;
  if(environment(me)!=this_object())
  return;

switch(random(10)) { 
case 0 : 
message_vision("$N一提杆，钓到了一条"+ HIR "大鲤鱼"NOR +"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",HIR "大鲤鱼"NOR);
fish->set("long","这是一条大红鲤鱼。\n");
fish->set("value",100);
fish->move(me);
me->receive_damage("kee",15); 
break; 
case 1 : 
message_vision("$N猛一提杆，钓到了"+ CYN "一个破草帽"NOR +"，晦气，晦气。 \n",me); 
message_vision(HIW "$N看着破草帽不由的发呆了。 \n\n" NOR,me); 
me->receive_damage("kee",5); 
break; 
case 2 : 
message_vision("$N看到鱼漂晃动，$N心里一急，猛的一提杆，$N钓到了"+ RED "一件红色的肚兜。 \n"NOR,me); 
message_vision(HIB "$N连声叫到：晦气，晦气。 \n\n" NOR,me); 
me->receive_damage("kee",7); 
break; 
case 3 : 
message_vision("$N一提杆，钓到了一条"+ HIC "鲶鱼"NOR +"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",HIC "鲶鱼"NOR);
fish->set("long","这是一条鲶鱼。\n");
fish->set("value",80);
fish->move(me);
me->receive_damage("kee",6); 
break; 
case 4 : 
message_vision("$N一提杆，钓到了一条"+ HIG "鲑鱼"NOR +"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",HIG "鲑鱼"NOR);
fish->set("long","这是一条鲑鱼。\n");
fish->set("value",50);
fish->move(me);
me->receive_damage("kee",12); 
break; 
case 5 : 
message_vision("$N一提杆，钓到了一条"YEL"草鱼"NOR"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",YEL"草鱼"NOR);
fish->set("long","这是一条草鱼。\n");
fish->set("value",30);
fish->move(me);
me->receive_damage("kee",10); 
break; 
case 6 : 
message_vision("$N一提杆，钓到了一条"+ HIB "鲟鱼"NOR +"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",HIB "鲟鱼"NOR);
fish->set("long","这是一条鲟鱼。\n");
fish->set("value",50);
fish->move(me);
me->receive_damage("kee",5); 
break; 
case 7 : 
message_vision("$N猛一提杆，钓到了"+ WHT "一个废旧的睡袋"NOR +"，晦气，晦气。 \n",me); 
message_vision(HIY"$N看着废旧的睡袋，眼睛立刻红了。 \n\n"NOR,me); 
me->receive_damage("kee",3); 
break; 
case 8 : 
message_vision("$N猛的一提杆，扯的太急了，线断了，鱼跑了，可惜，可惜。 \n",me); 
message_vision(HIC "$N不由的在心里大骂：%%$#@@#@**。 \n\n" NOR,me); 
me->receive_damage("kee",7); 
break; 
default : 
message_vision("$N一提杆，钓到了一条"+ HIM "娃娃鱼"NOR +"，恭喜，恭喜。 \n\n",me); 
fish=new(__DIR__"obj/fish");
fish->set("name",HIM "娃娃鱼"NOR);
fish->set("long","这是一条娃娃鱼。\n");
fish->set("value",120);
fish->move(me);
me->receive_damage("kee",8); 
break; 
} 
me->start_busy(random(2)); 

me->delete_temp("is_fishing");

return; 
} 

int valid_leave(object me,string dir)
{
   if(me->query_temp("is_fishing"))
   return notify_fail("既然已经开始钓鱼了，就把事情做完再走吧！\n");
   
   return ::valid_leave(me,dir);
   
}