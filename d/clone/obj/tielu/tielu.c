/*******************************************************************************
 炼铁炉.
 可以将 兵器、矿石放进去来炼成好的矿石。不过要消耗内力和气血。
 矿石的伤害力与铁匠的锻造技术有关
 矿石的坚强度与铁匠的膂力有关。
*********************************************************************************/
inherit ITEM;
#include <ansi.h>
#define TB this_object()
#define OB this_player()
int do_fire();
int do_put(string arg);
int do_la(string arg);
int do_ximie();
int do_kailu();
void create()
{
   set_name("炼铁炉", ({ "tie lu","lu"}) );
   set_weight(50000000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("long","这是一个炼铁的钢炉，铁匠都是从这里炼铁的。\n旁边有一个使用说明的牌子[pai].\n");
     set("material", "精钢");
     set("unit", "座");
     set("value",0);
     
   }
   setup();
}
int is_get_of(object pal,object ob)
{
  return notify_fail("你费了半天劲，发现根本抬不起来这个炼铁炉。\n");
}
void init()
{
  add_action("do_fire","fire");
  add_action("do_put","put");
  add_action("do_la","la");
  add_action("do_ximie","ximie");
  add_action("do_kailu","kailu");
}
int is_owner(object ob)
{
  if(TB->query("owner")==ob)
  return 1;
  return 0;
}
int do_fire()
{
  if(TB->query("fired"))
  return notify_fail("这个炉子已经被点着了，你要重新使用请熄灭[ximie]它吧！\n");
  if(OB->query("vocation")!="铁匠"||OB->query("family/family_name")!="东溟派")
  return notify_fail("只有东溟派铁匠可以使用这个炉子！\n");
  if(OB->query_skill("bihai-force",1)<200||OB->query_skill("force",1)<200)
  return notify_fail("你武功这么差不可以使用这个炉子！\n");
 if(time()-OB->query("lianzhi_busy")<1200)
return notify_fail("你还是先歇歇吧！\n");
  TB->set("fired",1);
  message_vision(HIR"$N只听炉子轰地一声，生起了熊熊大火！\n"NOR,OB);
  TB->set("name",HIR"炼铁炉"NOR);
  TB->set("owner",OB);
  return 1;
}

int do_ximie()
{
  if(!TB->query("fired"))
  return notify_fail("这个炉子没有点着，还用不着熄灭。\n");
  message_vision("$N小心翼翼地打开炉子，倒出了炉灰。\n",OB);
  TB->delete("fired");
  TB->delete("owner");
  TB->delete("ob");
  TB->set("name","炼铁炉");
  return 1;
}

int do_put(string arg)
{
  string name;object ob;
  if(!arg||
  sscanf(arg,"%s in 炼铁炉",name)!=1)
  return notify_fail("请使用 put xxx in 炼铁炉.\n");
  if(!TB->query("fired"))
  return notify_fail("这个炉子还没点着，先点着再放吧！\n");
  if(!is_owner(OB))
  return notify_fail("别人已经使用这个炉子了，你要使用，就先熄灭它吧！\n");
  if(!objectp(ob=present(name,OB)))
  return notify_fail("你的身上没有这个东西！\n");
  if(!ob->query("skill_type")&&!ob->query("weapon"))
  return notify_fail("这个东西不能用来炼铁！\n");
  if(ob->query("skill_type"))
  ob->unequip();
  message_vision("$N把"+ob->name()+"小心翼翼地放到了炼铁炉中。\n",OB);
  if(ob->query("skill_type")){
  TB->set("ob/damage",ob->query("weapon_prop/damage"));
  TB->set("ob/strong",ob->query("max_strong"));}
  else{
  TB->set("ob/damage",ob->query("weapon/damage"));
  TB->set("ob/strong",ob->query("weapon/strong"));}  
  destruct(ob);
  return 1;
}

int do_la(string arg)
{
  int damage,strong;
  if(!arg||arg!="风箱")
  return notify_fail("请使用la 风箱。\n");
  if(OB->is_busy())
  return notify_fail("你正忙着呢！\n");
  if(!TB->query("fired"))
  return notify_fail("火还没有点着，你拉什么风箱啊？\n");
  if(!is_owner(OB))
  return notify_fail("别人已经使用这个炉子了，你要使用，就先熄灭它吧！\n");
  if(!TB->query("ob"))
  return notify_fail("里面什么也没有，你拉风箱有什么用啊？\n");
  damage=TB->query("ob/damage");
  strong=TB->query("ob/strong");
  if(OB->query("force")<damage+strong)
  return notify_fail("你的内力不足以拉风箱了！\n");
  if(OB->query("kee")<damage*2+strong)
  return notify_fail(HIR"你感到气血翻滚，已经拉不动风箱了！\n"NOR);
  OB->add("force",-damage-strong);
  OB->receive_damage("kee",damage*2+strong);
  TB->add("ob/damage",OB->query_skill("duanzao-jishu",1)/70);
  TB->add("ob/strong",OB->query_str()/45);
  message_vision(HIR"$N运足力气拉了一下风箱，$N脸被炉火映得通红！\n"NOR,OB);
  OB->start_busy(3);
  return 1;
}
int do_kailu()
{
  object ob;
  if(!TB->query("fired"))
  return notify_fail("火还没有点着，你开什么炉啊？\n");
  if(!TB->query("ob"))
  return notify_fail("里面什么也没有，你开什么炉啊？\n");
  if(!is_owner(OB))
  return notify_fail("这是别人炼好的，你不能来开炉！\n");
  ob=new(__DIR__"tie");
  ob->set("weapon/strong",TB->query("ob/strong"));
  ob->set("weapon/damage",TB->query("ob/damage"));
  message_vision(HIR"$N小心翼翼地打开炉子，用铁钳夹出了一个通红的铁块。\n"NOR,OB);
  ob->move(environment(OB));
OB->set("lianzhi_busy",time());
  TB->delete("fired");
  TB->delete("owner");
  TB->delete("ob");
  TB->set("name","炼铁炉");
  return 1;
}
