
#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
	set_name(HIB"盘龙"NOR, ({ "pan long","whip" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long","这是一把武林中至宝兵器，名为「盘龙之鞭」。\n");
		set("value", 400);
		//set("super",9);
		set("material", "steel");
		set("weapon_prop/dodge",160);
		set("weapon_prop/whip",70);
		set("weapon_prop/parry",60);
		
	}
	init_whip(200,300,300);

	set("wield_msg", HIC"$N"+HIC+"「唰」地一声抽$n"+HIC+"，只见天地之间打了个闪电。\n"NOR);
	set("unwield_msg", "$N将手中的$n插入腰间的刀鞘。\n");


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
    owner->add("max_kee",900);
       
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
    
    owner->add("max_kee",-900);
    	if(owner->query("eff_kee")>owner->query("max_kee")){
      owner->set("eff_kee",owner->query("max_kee"));
      owner->set("kee",owner->query("max_kee"));}
    
   
    return 1;
}
