
#include <armor.h>
#include <ansi.h>

inherit ARMOR;

int query_autoload()
{
	return 1;
}

void create()
{
   set_name(HIY"金鳞"NOR, ({ "jin lin","armor"}) );
   set_weight(3000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("material", "铁");
     set("unit", "件");
     set("value",400);
     set("long","这是武林中的至宝，名为「蛟龙之金鳞」。\n");
     set("armor_prop/armor", 200);
     set("armor_prop/dodge_skill",40);
      set("armor_prop/jiaolong", 1);
   }
   setup();
}

int wear()
{
   object owner;
   
   if(!(owner = environment())->is_character()) return 0;
   
   if(!::wear()) return ::wear();
   
   if(owner->query("combat_exp")<1000000)
    return notify_fail("你目前无法装备这件物品。\n");
   
    if(owner->query_temp("apply/jiaolong")==5){
    	message_vision(HIC"$N"+HIC+"的身上发出龙吟般的声音，久久不绝。\n"NOR,owner);
    	owner->add_temp("apply/damage",100);
    	owner->add("max_kee",500);
    	owner->add("max_force",2000);}
    	
   return 1;
}

int unequip()
{
   object owner;
    
    if(!environment()) return 0;
    if( !(owner = environment())->is_character() ) return 0;
    
    if(!::unequip()) return ::unequip();
   
    if(owner->query_temp("apply/jiaolong")==4){
    	owner->add_temp("apply/damage",-100);
    	owner->add("max_kee",-500);
    	if(owner->query("eff_kee")>owner->query("max_kee")){
      owner->set("eff_kee",owner->query("max_kee"));
      owner->set("kee",owner->query("max_kee"));}
    	owner->add("max_force",-2000);
    	if(owner->query("force")>owner->query("max_force"))
      owner->set("force",owner->query("max_force"));}
    
    return 1;
}