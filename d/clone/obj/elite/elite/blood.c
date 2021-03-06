
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIR"血"NOR, ({ "xue","sword" }) );
	set_weight(7000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long","这是一把武林中至宝兵器，名为「莫邪之血」。\n");
		set("value", 400);
		//set("super",9);
		set("material", "steel");
		set("weapon_prop/dodge",100);
		set("weapon_prop/sword",40);
		set("weapon_prop/moye",1);
	}
	init_sword(250,300,300);

	set("wield_msg", HIR"$N"+HIR+"「唰」地一声抽$n"+HIR+"，只见一阵的红晕慢慢地散了出来。\n"NOR);
	set("unwield_msg", "$N将手中的$n插入腰间的剑鞘。\n");


	setup();
}


int wield()
{
    object owner;
    
    if(!environment()) return 0;
    if( !(owner = environment())->is_character() ) return 0;
    
    if(!::wield()) return ::wield();
    
    if(owner->query("combat_exp")<3000000)
    return notify_fail("你目前无法装备这件物品。\n");
    
    owner->add("max_force",500);
    owner->add("max_sen",500);
    owner->add("eff_sen",500);
    
    if(owner->query_temp("apply/moye")==4){
    	message_vision(HIR"$N"+HIR+"的身上冒出阵阵红晕，久久不见消散。\n"NOR,owner);
    	owner->add_temp("apply/damage",100);
    	owner->add_temp("apply/dodge",100);
    	owner->add("max_kee",500);
    	owner->add("max_force",1000);}
    
    return 1;
}

int unequip()
{
   object owner;
    
    if(!environment()) return 0;
    if( !(owner = environment())->is_character() ) return 0;
    
    if(!::unequip()) return ::unequip();
    owner->add("max_force",-500);
    if(owner->query("force")>owner->query("max_force"))
      owner->set("force",owner->query("max_force"));
    owner->add("max_sen",-500);
    owner->add("eff_sen",-500);
    if(owner->query("sen")>owner->query("eff_sen"))
      owner->set("sen",owner->query("eff_sen"));
    
    if(owner->query_temp("apply/moye")==3){
    	owner->add_temp("apply/damage",-100);
    	owner->add_temp("apply/dodge",-100);
    	owner->add("max_kee",-500);
    	if(owner->query("eff_kee")>owner->query("max_kee")){
      owner->set("eff_kee",owner->query("max_kee"));
      owner->set("kee",owner->query("max_kee"));}
    	owner->add("max_force",-1000);
    	if(owner->query("force")>owner->query("max_force"))
      owner->set("force",owner->query("max_force"));}
    
    return 1;
}
