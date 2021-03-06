
#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name(HIR"彩羽"NOR, ({ "cai yu","dagger" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 300);
		set("long","这是一把武林至宝短兵刃，名为「飞凤之彩羽」。\n");
		set("material", "steel");
		set("weapon_prop/dodge",80);
		set("weapon_prop/dagger",50);
		set("weapon_prop/feifeng",1);
	}
	init_dagger(200,300,300);

	set("wield_msg", HIR"$N"+HIR+"从怀中摸出一把$n"+HIR+"握在手中，只见一道彩光照亮了四周。\n"NOR);
	set("unwield_msg", "$N将手中的$n藏入怀中。\n");


	setup();
}

int wield()
{
    object owner;
    
    if(!environment()) return 0;
    if( !(owner = environment())->is_character() ) return 0;
    
    if(!::wield()) return ::wield();
    
    if(owner->query("combat_exp")<2000000)
    return notify_fail("你目前无法装备这件物品。\n");
    
    if(owner->query_temp("apply/feifeng")==5){
    	message_vision(HIY"$N"+HIY+"的身上现出阵阵彩色的幻象，久久不见消失。\n"NOR,owner);
    	owner->add_temp("apply/damage",100);
    	owner->add("max_kee",1000);
    	owner->add("max_force",200);
    	owner->add_temp("apply/dagger",50);}
    
    return 1;
}

int unequip()
{
   object owner;
    
    if(!environment()) return 0;
    if( !(owner = environment())->is_character() ) return 0;
    
    if(!::unequip()) return ::unequip();
    
    if(owner->query_temp("apply/feifeng")==4){
    	owner->add_temp("apply/damage",-100);
    	owner->add("max_kee",-1000);
    	if(owner->query("eff_kee")>owner->query("max_kee")){
      owner->set("eff_kee",owner->query("max_kee"));
      owner->set("kee",owner->query("max_kee"));}
      
      owner->add("max_force",-200);
    if(owner->query("force")>owner->query("max_force"))
      owner->set("force",owner->query("max_force"));
      
      owner->add_temp("apply/dagger",-50);}
    
    return 1;
}
