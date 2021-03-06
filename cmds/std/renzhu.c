
#include <dbase.h>
#include <ansi.h>

#include "tiejiang.h"

string *msg=({
HIY"$N"+HIY+"渐渐流下了汗，炉子的火越来越旺了！\n"NOR,
HIR"只见火势越来越旺，$N"+HIR+"有些受不了了。\n"NOR,
HIB"$N"+HIB+"不停的挥舞着铁锤，乒乒乓乓地敲打着兵器！\n"NOR,
HIB"$N"+HIB+"不停的挥舞着铁锤，乒乒乓乓地敲打着兵器！\n"NOR,
RED"$N"+RED+"有些气喘吁吁，脸被火光映得通红。\n"NOR,
YEL"$N"+YEL+"将附在兵器上的意识一点点的抹去。\n"NOR,
YEL"$N"+YEL+"灌注心血，重新为兵器附上灵性。\n"NOR,

});

int check_legal_id(string id);

int main(object ob,string arg)
{
	object weapon,iron;
	string id,weapon_name;	
	int strong,max_strong;
	string j="";
	
	if(ob->query("vocation")!="铁匠")
	return notify_fail("只有铁匠才能给兵器确定主人。\n");
	
	if(ob->query_skill("duanzao-jishu",1)<60)
	return notify_fail("你的锻造技术太低了，无法给兵器确定主人。\n");
	
	if(ob->query("max_force")<1000)
	return notify_fail("你的内力修为太低，无法给兵器确定主人！\n");	
	
	if(member_array(base_name(environment(ob)),tiejiang_here)==-1)
        return notify_fail("你还是到兵器店去给兵器确定主人吧！\n");	
	
	if(ob->is_fighting())
	 return notify_fail("你还在打仗呢！\n");
	
	if(ob->is_busy())
	 return notify_fail("你正忙着呢！\n");
	
	if(!arg)
		return notify_fail("请使用 renzhu 兵器 with 主人id。\n");
	if(sscanf(arg,"%s with %s",weapon_name,id)!=2)
	    return notify_fail("请使用 renzhu 兵器 with 主人id。\n");
	
	if(!check_legal_id(id))
	 return 1;
	 
	if(!objectp(weapon=present(weapon_name,ob)))
		return notify_fail("你身上并没有这个兵器!\n");
	
	if(!weapon->is_dazao())
		return notify_fail("这个兵器不能被确定主人！\n");
	
	if(weapon->query("user")!="")
		return notify_fail("这个兵器已经有主人了！\n");
   
	if(!weapon->query("skill_type"))
		return notify_fail("你只能给武器确定主人！\n");
        
	 if(userp(ob)&&ob->query("gin")<800)
	 return notify_fail("你发现以你现在的精血无法给兵器确定主人。\n");
        
	message_vision("$N把"+weapon->query("name")+"放到"+environment(ob)->query("short")+"的铁炉上。\n",ob);
	message_vision(RED"\n$N"+RED+"拉动风箱，火“呼”地一声窜了起来！\n"NOR,ob);
	
	if(userp(ob))
	 ob->receive_damage("gin",800);
		
	ob->start_busy(5);
	
	call_out("do_msg",5,ob,weapon,id,0);
	
	return 1;
	
	
}

void do_msg(object ob,object weapon,string id,int times)
{
	int rate=0;
	
	if(!ob||!weapon||environment(weapon)!=ob)
		return;
	
	if(times>=sizeof(msg)){
		weapon->set("user",id);
		
		tell_object(ob,HIC"终于这把兵器具有的灵性已经足够认识自己的主人了。\n"NOR,);
		
		return;
    }
    message_vision(msg[times]+"\n",ob);
    ob->start_busy(5);
    
    call_out("do_msg",5,ob,weapon,id,times+1);
    
}



int check_legal_id(string id)
{
	int i;
	i = strlen(id);
	if((strlen(id) < 3) || (strlen(id) > 8)) 
	{
		write("对不起，主人的名字必须是 3 到 8 个英文字母。\n");
		return 0;
	}
	while(i--)
		if(id[i]<'a' || id[i]>'z') 
		{
			write("对不起，主人的英文名字只能用英文字母。\n");
			return 0;
		}
	
	return 1;
}