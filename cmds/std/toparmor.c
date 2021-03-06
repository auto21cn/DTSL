//在线盔甲排行榜
//进入排行榜的条件：damage>100
//默认只列出前10名。最多列出 50 名。
#include <ansi.h>
inherit F_DBASE;

int sort_user(object,object);
int get_damage(object ob);
string left(string str,int longnumber);

int ifselect(object ob,int damage)
{
  if(get_damage(ob)>=damage)
  return 1;
  else
  return 0;
  
}

int main(object me,string arg)
{
        
        int number;
        object *weapons;
        string msg;
        int i,j;
        int base_damage=100;
        float d_rate=1.0;
        
        if(!arg||sscanf(arg,"%d",number)!=1)
          number=10;
        if(number>50) number=50;
        
        if(!arrayp(weapons=objects((: !living($1) && environment($1) :))))
         return notify_fail("你什么也找不到。\n");
        
        do{
        if(!arrayp(weapons=filter_array(weapons,(: 
              ($1->query("skill_type")&&
              environment($1)&&
              userp(environment($1))&&
              $1->query("weapon_prop/damage")&&
              $1->query("save_flag")            
              )
              :)
              ))) 
        return notify_fail("目前江湖上没有人有什么好兵器。\n");
        weapons=filter_array(weapons,"ifselect",this_object(),(int)(base_damage*d_rate));
        d_rate+=0.2;
        }
        while(sizeof(weapons)>=300);
        
        if(sizeof(weapons)<=0)
        return notify_fail("目前江湖上没有人有什么好兵器。\n");
        weapons=sort_array(weapons,(:sort_user:));
        msg=HIC"大唐双龙在线神兵利器排行榜:\n"NOR;
        msg +=HIB"━━━━━━━━━━━━━━━━━━━━━━━\n"NOR;
        for(i=0;i<sizeof(weapons)&&i<number;i++){
         msg +=left(weapons[i]->name(),30);
         msg +="目前在"+environment(weapons[i])->query("name")+"身上\n";}
        msg +="\n";
        msg +=HIB"━━━━━━━━━━━━━━━━━━━━━━━\n"NOR;
        me->start_more(msg);
        return 1;
}

int get_damage(object ob)
{
  int score;
    
  score=ob->query("weapon_prop/damage",1)+
        ob->query("weapon_prop/min_damage",1)+
        ob->query("weapon_prop/dodge",1)/10+
        ob->query("weapon_prop/armor",1)/10+
        ob->query("weapon_prop/enhance_min_damage",1)/5+
        ob->query("weapon_prop/enhance_max_damage",1)/5+
        ob->query("weapon_prop/double_damage",1)/5+
        ob->query("weapon_prop/strength",1)*2+
        ob->query("weapon_prop/intelligence",1)*2+
        ob->query("weapon_prop/constitution",1)*2+
        ob->query("weapon_prop/dodgeaction",1)*2+
        ob->query("weapon_prop/personality",1)*2+
        ob->query("weapon_prop/karma",1)*2+
        ob->query("weapon_prop/no_need_force",1)*10+
        ob->query("weapon_prop/no_need_maxforce",1)*10+
        ob->query("weapon_prop/no_need_sx",1)*10+
        ob->query("weapon_prop/reduce_force",1)*2+
        ob->query("weapon_prop/reduce_maxforce",1)*2+
        ob->query("weapon_prop/reduce_sx",1)*2+
        ob->query("user_skill",1)/10;
       
     return score;
}

int sort_user(object ob1,object ob2)
{
    return get_damage(ob2)-get_damage(ob1);
}

string no_color(string arg)
{
        arg = replace_string(arg,  BLK, "");
	arg = replace_string(arg,  RED, "");
	arg = replace_string(arg,  GRN, "");
	arg = replace_string(arg,  YEL, "");
	arg = replace_string(arg,  BLU, "");
	arg = replace_string(arg,  MAG, "");
	arg = replace_string(arg,  CYN, "");
	arg = replace_string(arg,  WHT, "");
	arg = replace_string(arg,  HIR, "");
	arg = replace_string(arg,  HIG, "");
	arg = replace_string(arg,  HIY, "");
	arg = replace_string(arg,  HIB, "");
	arg = replace_string(arg,  HIM, "");
	arg = replace_string(arg,  HIC, "");
	arg = replace_string(arg,  HIW, "");
	arg = replace_string(arg,  NOR, "");
	arg = replace_string(arg,  BLINK, "");
	return arg;
}

string left(string str,int longnumber)
{
	int space,len,i;
	string s,olds;
	olds=str;
	s="";
	str=no_color(str);
	len=strlen(str);
	space=(longnumber-len);
	for(i=0;i<space;i++) s+=" ";
	return sprintf("%s%s",olds,s);
}

int help(object me)
{
  write(@HELP
指令格式 : topweapon <数字>
 
这个指令可以显示大唐双龙的「神兵利器」排行榜。
使用 topweapon ,则可以显示前10名，使用 topweapon 数字，
则可以显示 前 数字 名。如 topweapon 20,则可以显示前20
名。topweapon 最多支持到前 50 名。

注意：因为系统中武器会有很多，为了减少负担，系统会尽量
寻找好的兵器，很可能在前一分钟你的兵器会上排行榜，而下
一分钟将不会出现在上面。
此排行榜为在线排行，退出游戏不会被计算在内。

HELP
    );
    return 1;
}