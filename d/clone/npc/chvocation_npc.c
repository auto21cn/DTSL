#include <ansi.h>
inherit NPC;

string *vocations=({"兵器类铁匠","护具类铁匠","毒药系铁匠",
	"明药师","暗药师","杀手"});

void create()
{
        set_name("天竺高僧",({ "gao seng","gao","seng"}) );
        set("gender", "男性" );
        set("class","bonze");
        set("long","这是位天竺高僧，据说功力不凡。\n");
        set("age", 32);
				set("inquiry",([
					"转换职业":"我能转换的职业为\n"+
					         "兵器类铁匠、护具类铁匠、毒药系铁匠、明药师、暗药师、杀手。\n"+
					         "你可以使用命令 zhuanzhi 来转换职业。\n",
				]));         
        set("target_id","####");
        
    setup();
    
}

void init()
{
	add_action("do_change_vocation","zhuanzhi");
	
}
  
int do_change_vocation(string arg)
{
	object ob;
	
	ob=this_player();
	
	if(!ob->query("vocation")){
		command("say 你没选择职业，现在不用转换职业。");
		return 1;
	}
	if(!arg)
		return notify_fail("你要转换为什么职业？\n");
	/*if(ob->query("change_vocation")){
		command("say 你已经转换一次职业了，不能转换了！");
		return 1;
	}
	*/
	switch(arg){
		case "兵器类铁匠":  
			if(ob->query("vocation_fenzhi")=="weapon")
				return notify_fail("你本来就是兵器类铁匠。\n");
			if(ob->query("vocation")=="药师"){
				if(ob->query_skill("poison",1))
					ob->delete_skill("poison");
				else
					ob->delete_skill("bencao-shuli");
			}
			if(ob->query("vocation")=="杀手"){
				ob->delete_skill("yingzi-jianfa");
			}
			ob->set("vocation","铁匠");
			ob->set("vocation_fenzhi","weapon");
			break;
		
		case "护具类铁匠":  
			if(ob->query("vocation_fenzhi")=="armor")
				return notify_fail("你本来就是护具类铁匠。\n");
			if(ob->query("vocation")=="药师"){
				if(ob->query_skill("poison",1))
					ob->delete_skill("poison");
				else
					ob->delete_skill("bencao-shuli");
			}
			if(ob->query("vocation")=="杀手"){
				ob->delete_skill("yingzi-jianfa");
			}
			ob->set("vocation","铁匠");
			ob->set("vocation_fenzhi","armor");
			break;	
		
		case "毒药系铁匠":  
			if(ob->query("vocation_fenzhi")=="poison")
				return notify_fail("你本来就是毒药系铁匠。\n");
			if(ob->query("vocation")=="药师"){
				if(ob->query_skill("poison",1))
					ob->delete_skill("poison");
				else
					ob->delete_skill("bencao-shuli");
			}
			if(ob->query("vocation")=="杀手"){
				ob->delete_skill("yingzi-jianfa");
			}
			ob->set("vocation","铁匠");
			ob->set("vocation_fenzhi","poison");
			break;	
		
		case "明药师":
			if(ob->query("vocation")=="药师")
				if(ob->query_skill("bencao-shuli",1))
					return notify_fail("你本来就是明药师。\n");
			
			if(ob->query("vocation")=="药师")
				ob->delete_skill("poison");
			if(ob->query("vocation")=="杀手"){
				ob->delete_skill("yingzi-jianfa");
			}
			if(ob->query("vocation")=="铁匠"){
				ob->delete_skill("duanzao-jishu");
				ob->delete("vocation_fenzhi");
			}
			ob->set("vocation","药师");
			break;
		
		case "暗药师":
			if(ob->query("vocation")=="药师")
				if(ob->query_skill("poison",1))
					return notify_fail("你本来就是暗药师。\n");
			
			if(ob->query("vocation")=="药师")
				ob->delete_skill("bencao-shuli");
			if(ob->query("vocation")=="杀手"){
				ob->delete_skill("yingzi-jianfa");
			}
			if(ob->query("vocation")=="铁匠"){
				ob->delete_skill("duanzao-jishu");
				ob->delete("vocation_fenzhi");
			}
			ob->set("vocation","药师");
			break;
		
		case "杀手":
			if(ob->query("vocation")=="杀手")
				return notify_fail("你本来就是杀手。\n");
			if(ob->query("vocation")=="铁匠"){
				ob->delete_skill("duanzao-jishu");
				ob->delete("vocation_fenzhi");
			}
			if(ob->query("vocation")=="药师"){
				if(ob->query_skill("poison",1))
					ob->delete_skill("poison");
				else
					ob->delete_skill("bencao-shuli");
			}
			ob->set("vocation","杀手");
		  break;
		default:
			return notify_fail("你只能转换的职业为"+
				"兵器类铁匠、护具类铁匠、毒药系铁匠、明药师、暗药师、杀手。\n");
	}
	
	ob->set("change_vocation",time());
	ob->add("combat_exp",-ob->query("combat_exp")/100);
	
	command("say 职业转换完毕！");
	
	return 1;
	
}
			
