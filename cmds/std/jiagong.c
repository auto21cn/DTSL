
#include <dbase.h>
#include <ansi.h>

#include "tiejiang.h"

string *msg=({
HIY"$N"+HIY+"渐渐流下了汗，炉子的火越来越旺了！\n"NOR,
HIY"$N"+HIY+"渐渐流下了汗，炉子的火越来越旺了！\n"NOR,
HIR"只见火势越来越旺，$N"+HIR+"有些受不了了。\n"NOR,
HIR"只见火势越来越旺，$N"+HIR+"有些受不了了。\n"NOR,
HIB"$N"+HIB+"不停的挥舞着铁锤，乒乒乓乓地敲打着兵器！\n"NOR,
HIB"$N"+HIB+"不停的挥舞着铁锤，乒乒乓乓地敲打着兵器！\n"NOR,
RED"$N"+RED+"有些气喘吁吁，脸被火光映得通红。\n"NOR,
RED"$N"+RED+"有些气喘吁吁，脸被火光映得通红。\n"NOR,
});

void bad_weapon(object weapon);
void good_weapon(object weapon,int rate,int u_rate);

int main(object ob,string arg)
{
	object weapon,iron;
	string iron_name,weapon_name;	
	int strong,max_strong;
	string j="";
	
	if(ob->query("vocation")!="铁匠")
	return notify_fail("只有铁匠才能加工兵器。\n");
	
	if(ob->query_skill("duanzao-jishu",1)<60)
	return notify_fail("你的锻造技术太低了，无法加工兵器。\n");
	
	if(ob->query("max_force")<1000)
	return notify_fail("你的内力修为太低，无法加工兵器！\n");
        
        if(member_array(base_name(environment(ob)),tiejiang_here)==-1)
        return notify_fail("你还是到兵器店去加工兵器吧！\n");		
	
	if(ob->is_fighting())
	 return notify_fail("你还在打仗呢！\n");
	
	if(ob->is_busy())
	 return notify_fail("你正忙着呢！\n");
	
	if(!arg)
		return notify_fail("请使用 jiagong 兵器 with 矿石。\n");
	if(sscanf(arg,"%s with %s",weapon_name,iron_name)!=2)
	    return notify_fail("请使用 jiagong 兵器 with 矿石。\n");
	if(!objectp(weapon=present(weapon_name,ob)))
		return notify_fail("你身上并没有这个兵器!\n");
	
	if(!weapon->is_dazao())
		return notify_fail("这个兵器不能被加工！\n");
	
	if(weapon->query("jiagong"))
		return notify_fail("这个兵器已经加工过了！\n");
    if(!objectp(iron=present(iron_name,ob)))
		return notify_fail("你身上并没有这种矿石!\n");
	if(!iron->query("weapon"))
		return notify_fail(iron->query("name")+"不是矿石。\n");
	if(!weapon->query("skill_type"))
		return notify_fail("你只能加工武器！\n");
    
    strong=(int)weapon->query("strong",1);
	max_strong=(int)weapon->query("max_strong",1);
	 	
	 if(userp(ob)&&ob->query("gin")<800)
	 return notify_fail("你发现以你现在的精血无法加工兵器。\n");
        
	message_vision("$N把"+weapon->query("name")+"放到"+environment(ob)->query("short")+"的铁炉上。\n",ob);
	message_vision(RED"\n$N"+RED+"拉动风箱，火“呼”地一声窜了起来！\n"NOR,ob);
	
	if(userp(ob))
	 ob->receive_damage("gin",800);
	
	if(iron->query_amount()&&
	 iron->query_amount()>1)
	 iron->set_amount(iron->query_amount()-1);
	else
        destruct(iron);
        
	ob->start_busy(5);
	
	call_out("do_msg",5,ob,weapon,0);
	
	return 1;
	
	
}

void do_msg(object ob,object weapon,int times)
{
	int rate=0;
	int u_rate=0;
	
	if(!ob||!weapon||environment(weapon)!=ob)
		return;
	
	if(times>=sizeof(msg)){
		weapon->set("jiagong",1);
		if(present("bingpo shenzhu",ob)||present("huolong neidan",ob))
			rate=10;
			u_rate=3;
		rate+=random(ob->query_skill("duanzao-jishu",1)/10);
		if(random(ob->query_kar())<ob->query_kar()-3){
		 tell_object(ob,"\n无论你怎么样努力，这样兵器最后还是无法突破它的局限，终于达到极限崩溃了。\n");
			bad_weapon(weapon);
		}
		else{
		 tell_object(ob,"\n经过你的努力，这样兵器终于突破限制，超越了本身。\n");
		 good_weapon(weapon,rate,u_rate);
		}
		ob->add("max_force",-2);
		return;
    }
    message_vision(msg[times]+"\n",ob);
    ob->start_busy(5);
    
    call_out("do_msg",5,ob,weapon,times+1);
    
}

void bad_weapon(object weapon)
{
	weapon->set("weapon_prop/damage",weapon->query("weapon_prop/damage")/3);
	weapon->set("weapon_prop/min_damage",weapon->query("weapon_prop/min_damage")/3);
	if(random(100)>60)
	 weapon->set("weapon_prop/enhance_min_damage",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/intelligence",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/dodge",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/karma",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/dodgeaction",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/constitution",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/personality",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/armor",0);
	if(random(100)>60)
	 weapon->set("weapon_prop/strength",0);
	
}

void good_weapon(object weapon,int rate,int u_rate)
{
	
	if(random(100)>u_rate) rate=1+random(2);
	else rate=random(10);
	
	weapon->add("weapon_prop/min_damage",random(rate)*10+1);
	if(weapon->query("weapon_prop/min_damage")>weapon->query("weapon_prop/damage"))
	weapon->set("weapon_prop/min_damage",weapon->query("weapon_prop/damage"));
	
	if(random(100)>90)
	 weapon->add("weapon_prop/enhance_min_damage",random(rate)+random(10)+5);
	else
	if(random(100)>60)
	 weapon->add("weapon_prop/enhance_min_damage",random(10));
	
	if(random(100)>90)
	 weapon->add("weapon_prop/enhance_max_damage",random(rate)+random(10)+5);
	else
	if(random(100)>60)
	 weapon->add("weapon_prop/enhance_max_damage",random(10));
	
	if(random(100)>90)
	 weapon->add("weapon_prop/double_damage",random(rate));
	else
	if(random(100)>60)
	 weapon->add("weapon_prop/double_damage",random(5));
	 	
	if(random(100)>80)
	 weapon->add("weapon_prop/dodge",random(rate)+random(10)+5);
	else
	if(random(100)>60)
	 weapon->add("weapon_prop/dodge",random(10)+5);
	 
	if(random(100)>80)
	 weapon->add("weapon_prop/armor",random(rate)+random(10)+5);
	else
	if(random(100)>60)
	 weapon->add("weapon_prop/armor",random(10)+5);
	
	if(random(100)>95)
	 weapon->add("weapon_prop/intelligence",random(rate/2)+1);	
	if(random(100)>95)
	 weapon->add("weapon_prop/karma",random(rate/2)+1);
	if(random(100)>95)
	 weapon->add("weapon_prop/dodgeaction",random(rate/2)+1);
	if(random(100)>95)
	 weapon->add("weapon_prop/constitution",random(rate/2)+1);
	if(random(100)>95)
	 weapon->add("weapon_prop/personality",random(rate/2)+1);
	
	if(random(100)>95)
	 weapon->add("weapon_prop/strength",random(rate/2)+1);
	
	if(random(100)>96)
	 weapon->add("super",1);
	 
}