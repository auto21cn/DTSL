//orgd.c
//dtsl for banghui function.

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

#define REPORT_ERROR "帮会系统出错，请报告巫师。\n"

string query_save_file()
{
  return "/data/orgd";
}

void create()
{
  set("name","帮会精灵");
  set("id","orgd.c");
  seteuid(getuid());
  restore();
}

string get_shili(object ob)
{
        if(!ob->query("shili/name")) return "没有加入帮会";
	if(ob->query("shili/name")=="duzun_b") return "独尊堡";
	else if(ob->query("shili/name")=="lifa_b") return "天策府";
	else if(ob->query("shili/name")=="songjia_b") return "宋阀";
	else if(ob->query("shili/name")=="dajiang_b") return "大江联";
	else if(ob->query("shili/name")=="haisha_b") return "海沙帮";
	else if(ob->query("shili/name")=="jianghuai_b") return "江淮军";
	else if(ob->query("shili/name")=="feima_b") return "飞马牧场";
	else return "势力不明";
}//in score.c
string query_guanzhi(object ob)
{
	if(ob->query("shili/leader"))
	   if(ob->query("shili/leader")=="lifa_b")
	     return "天策府阀主";
	   else if(ob->query("shili/leader")=="songjia_b")
	         return "宋阀阀主";
	   else if(ob->query("shili/leader")=="duzun_b")
	         return "独尊堡堡主";
	   else if(ob->query("shili/leader")=="dajiang_b")
	         return "大江联盟主";
	   else if(ob->query("shili/leader")=="haisha_b")
	         return "海沙帮帮主";
	   else if(ob->query("shili/leader")=="feima_b")
	         return "飞马场主";
	if(stringp(ob->query("shili/guanzhi")))
	 return ob->query("shili/guanzhi");
	return "无";
}//in  score.c

string query_short_guanzhi(object ob)
{
	if(ob->query("shili/leader"))
	   if(ob->query("shili/leader")=="lifa_b")
	     return "阀主";
	   else if(ob->query("shili/leader")=="songjia_b")
	         return "堡主";
	   else if(ob->query("shili/leader")=="duzun_b")
	         return "堡主";
	   else if(ob->query("shili/leader")=="dajiang_b")
	         return "盟主";
	   else if(ob->query("shili/leader")=="haisha_b")
	         return "帮主";
	   else if(ob->query("shili/leader")=="feima_b")
	         return "场主";
	if(stringp(ob->query("shili/guanzhi")))
	 return ob->query("shili/guanzhi");
	return "";
}//in who.c

string get_channel_shili(object ob)
{
	if(ob->query("shili/name")=="duzun_b") return "独尊堡";
	else if(ob->query("shili/name")=="lifa_b") return "天策府";
	else if(ob->query("shili/name")=="songjia_b") return "宋阀";
	else if(ob->query("shili/name")=="dajiang_b") return "大江联";
	else if(ob->query("shili/name")=="haisha_b") return "海沙帮";
	else if(ob->query("shili/name")=="jianghuai_b") return "江淮军";
	else if(ob->query("shili/name")=="feima_b") return "飞马牧场";
	else return "势力不明";
}

string get_board_shili(string str)
{
  switch(str){
  case "feima_b": return "飞马牧场";break;
  case "lifa_b":  return "天策府";break;
  case "duzun_b": return "独尊堡";break;
  case "songjia_b": return "宋阀";break;
  case "haisha_b": return "海沙帮";break;
  case "dajiang_b": return "大江联";break;
  default: return "错误的帮会";}

}
void org_delete(object me)
{
object sboard;mapping *notes;int num;
if(!me->query("shili/name")) return;
sboard=load_object(BOARD_PATH+me->query("shili/name"));
if(!sboard) return;
notes=sboard->query("notes");
if(!notes) return;
num=sizeof(notes);
while(num--){
if(notes[num]["id"]==me->query("id")){
notes = notes[0..num-1] + notes[num+1..<1];
me->delete("shili");
sboard->set("notes",notes);
sboard->save();
break;}}
return;
}

void org_lose(object ob)
{
	object sboard;
	sboard=load_object(BOARD_PATH+ob->query("shili/name"));
	if(!sboard) return;
	sboard->add("deadtimes",1);//the shili board add a deadtimes.
	sboard->add("exp",-ob->query("combat_exp")/100);
	sboard->add("money",-ob->query("combat_exp")/500);
	if(sboard->query("exp")<0)
	sboard->set("exp",0);
	if(sboard->query("money")<0)
	sboard->set("money",0);
	sboard->save();
	return;
}

int valid_discard(object ob,object board,string id)
{
  if( ob->query("shili/leader")!=board->query("board_id")
	&&wizhood(ob) != "(admin)" 
	&&wizhood(ob) != "(arch)"
	&&ob->query("id")!=id)
    return 0;
  return 1;
}

void save_obj(object me)
{
	object *inv;
  int i;
  
  if(!me) return;
  inv=all_inventory(me);
  for(i=0; i<sizeof(inv); i++)
  	inv[i]->query_autoload();
  
  me->save();
	
}

void clear_ob(object ob,object ob2)
{
  destruct(ob);
  destruct(ob2);
}

int org_del_member(object ob,object board,string id,string name,
                   mapping *notes,int i)
{
   object target,body;
   int flag=0;
   
   if(!ob->query("shili")
     &&!valid_discard(ob,board,id))
   return notify_fail("你无权将这个人赶出帮会！\n");
   if(ob->query("shili/name")!=board->query("board_id")
      &&!wizardp(ob))
   return notify_fail("喂，看清楚点，这是你的地盘吗？？\n");
   
   if(!target=find_player(id)){
        
     body=new(LOGIN_OB);
     if((string)body->set("id",id)!=id)
      return notify_fail(REPORT_ERROR);
     if(!body->restore()){
      destruct(body);
      return notify_fail("没有这个玩家，或者他已经自杀，或者他被巫师杀档了。\n");
     }
     body->set("body",USER_OB);
     target=LOGIN_D->make_body(body);
     if(!target->restore()){
       destruct(target);
       return notify_fail(REPORT_ERROR);
     }
     target->setup();
     
   }else
   flag=1;
   
   if(!ob->query("shili/power")
      &&!valid_discard(ob,board,id)){
    if(!flag)
     clear_ob(body,target);
    return notify_fail("小喽罗还是不要干这种事的好！\n");
   }
   
   if(target->query("shili/power")
      &&ob->query("shili/power")>=target->query("shili/power")
      &&!valid_discard(ob,board,id)){
     if(!flag)
     clear_ob(body,target);
     return notify_fail("你无权让对方退帮！\n");
   }
   if(ob->query("shili/leader")
     &&ob->query("id")==id){
     	if(!flag)
        clear_ob(body,target);
	return notify_fail("帮主不能退帮，只能用power 让位。\n");
  }
  if(target->query("shili/leader")
  		&&!valid_discard(ob,board,id)){
  	if(!flag)
        clear_ob(body,target);	
  	return notify_fail("你无权让对方退帮！\n");
  }
   if(flag&&ob->query("id")!=id){
      CHANNEL_D->do_channel( this_object(), "rumor",
	 sprintf("%s被%s赶出%s了。", 
	 target->name(),ob->name(),get_board_shili(board->query("board_id"))));
	 tell_object(target,HIR"\n你被赶出帮派了！\n\n"NOR);
   }
   if(!flag)
      CHANNEL_D->do_channel( this_object(), "rumor",
	sprintf("%s被%s赶出%s了。", 
	name,ob->name(),get_board_shili(board->query("board_id"))));
   if(ob->query("id")==id){
     CHANNEL_D->do_channel( this_object(), "rumor",
			sprintf("%s主动退出%s了。", 
		ob->name(),get_board_shili(board->query("board_id"))));
		ob->add("combat_exp",-ob->query("reward_exp"));
		ob->set("reward_exp",0);
   }
   
   if(ob->query("id")!=id)
   	tell_object(ob,HIR"\n你将 " + name + " 赶出了帮会。\n\n"NOR);   
   if(flag){
    target->delete("shili");   
   }
   else{
   	 target->delete("shili");
   	 save_obj(target);
   }
   notes = notes[0..i-1] + notes[i+1..<1];
   board->set("notes", notes);
   board->save();
   if(!flag)
   clear_ob(body,target);
   
   return 1;
   
}  
   
string *leader=({"songque","lishimin","xiehui","haisha","feima",
"dajiang"});

mapping org_friend=([
"songjia_b":({}),
"lifa_b":({}),
"duzun_b":({}),
"feima_b":({}),
"haisha_b":({}),
"dajiang_b":({}),

]);

string swap_org_name(string arg)
{
  switch(arg){
    case "宋阀": return "songjia_b";
    case "天策府": return "lifa_b";
    case "独尊堡": return "duzun_b";
    case "飞马牧场": return "feima_b";
    case "海沙帮": return "haisha_b";
    case "大江联": return "dajiang_b";
    default: return "error";
  }
  
}

string BangZhu_Id(string arg)
{
  switch(arg){
    case "songjia_b": return "songque";
    case "lifa_b": return "lishimin";
    case "duzun_b": return "xiehui";
    case "feima_b": return "feima";
    case "haisha_b": return "haisha";
    case "dajiang_b": return "dajiang";
    default: return "error";
  }  
}

string BangZhu_name(string arg)
{
  switch(arg){
    case "songjia_b": return "宋缺";
    case "lifa_b": return "李世民";
    case "duzun_b": return "解晖";
    case "feima_b": return "商秀珣";
    case "haisha_b": return "韩盖天";
    case "dajiang_b": return "郑淑明";
    default: return "error";
  }  
}

void add_leader(string arg)
{
   if(member_array(arg,leader)==-1)
    leader=leader+({arg});
   
   save();
   return;
}

int if_friend_org(object me,object ob)
{
   string org_me,orgs_me,org_ob,orgs_ob;
   
   org_me=me->query("shili/name");
   org_ob=ob->query("shili/name");
   orgs_me=org_friend[org_me];
   orgs_ob=org_friend[org_ob];
   
   if(arrayp(orgs_ob)&&arrayp(orgs_me)
    &&member_array(org_me,orgs_ob)!=-1
    &&member_array(org_ob,orgs_me)!=-1
     )
     return 1;
   
   return 0;
}

int list_friend_org(object ob)
{
   string org,*orgs;
   int i;
   string msg;
   
   org=ob->query("shili/name");
   orgs=org_friend[org];
   
   if(sizeof(orgs)<=0)
    return notify_fail("目前"+get_board_shili(org)+"没有和任何帮会结盟。\n");
   
   msg="\n\n目前已经结盟的帮会：\n\n";
   for(i=0;i<sizeof(orgs);i++)
    msg+=get_board_shili(orgs[i])+"\n\n";
   
   ob->start_more(msg);
   return 1;
}

int make_friend(object me,string arg)
{
    string org,*orgs;
    
    arg=swap_org_name(arg);
    if(arg=="error")
    return notify_fail("目前江湖上不存在这个帮会！\n");
    
    org=me->query("shili/name");
    orgs=org_friend[org];
    if(member_array(arg,orgs)!=-1)
    return notify_fail("你们已经结盟了！\n");
    orgs=orgs+({arg});
    org_friend[org]=orgs;
    save();
    CHANNEL_D->do_channel(this_object(),"rumor",
    get_board_shili(org)+"和"+get_board_shili(arg)+"结盟了！\n");
    
    return 1;
}

int make_enemy(object me,string arg)
{
    string org,*orgs;
    
    arg=swap_org_name(arg);
    if(arg=="error")
    return notify_fail("目前江湖上不存在这个帮会！\n");
    
    org=me->query("shili/name");
    orgs=org_friend[org];
    if(member_array(arg,orgs)==-1)
    return notify_fail("你们还没有结盟，无法解盟！\n");
    orgs=orgs-({arg});
    org_friend[org]=orgs;
    save();
    CHANNEL_D->do_channel(this_object(),"rumor",
    get_board_shili(org)+"和"+get_board_shili(arg)+"解盟了！\n");
    
    return 1;
}

void del_leader(string arg)
{
   if(member_array(arg,leader)==-1)
   return;
   leader=leader-({arg});
   save();
   return;
}

int is_leader(string arg)
{
  if(member_array(arg,leader)==-1)
  return 0;
  return 1;
}

void set_leader_log(object ob,object obj)
{
  log_file("org/"+ob->query("shili/name")+"_bangzhu",
   ob->name()+"代替"+obj->name()+"成为"+get_board_shili(ob->query("shili/name"))+"首领。"+
   "时间："+ctime(time())+"。\n");
  
  return;
  
}

void purge_leader_log(object ob,object obj)
{
  log_file("org/"+obj->query("shili/name")+"_bangzhu",
   ob->name()+"取消了"+obj->name()+"的"+get_board_shili(obj->query("shili/name"))+"首领职位。"+
   "时间："+ctime(time())+"。\n");
  
  return;
  
}

int ShiZhong_BangZhu(object ob,string id)
{
   object target,body;
   int flag=0;
   
        seteuid(id);
        body = new(USER_OB);
        export_uid(body);
     body->set("id", id);
     if(!body->restore()){
       destruct(body);
           tell_object(ob,HIR"没有这个玩家！\n"NOR); 
       return 0;
     }
  if(!body->query("shili/leader")){

       destruct(body);
    tell_object(ob,HIR"他是帮主吗？\n"NOR); 
  	return 0;
  }
      CHANNEL_D->do_channel( this_object(), "rumor",
	 sprintf("%s失踪多日，为了不影响帮务的正常进行，由原始帮主%s继任。", query_guanzhi(body),BangZhu_name(body->query("shili/name"))));

		body->add("combat_exp",-ob->query("reward_exp"));
		body->set("reward_exp",0);
   
   	body->delete("shili/leader");
   	purge_leader_log(ob,body);
    add_leader(BangZhu_Id(body->query("shili/name")));   
   	 save_obj(body);   
   return 1;
} 

mapping base_skill=([

"songjia_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),
"lifa_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),
"feima_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),
"duzun_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),
"dajiang_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),
"haisha_b":([
               "force":400,
               "dodge":400,
               "cuff":400,
               "blade":400,
               "sword":400,
               "strike":400,
               "finger":400,
               "leg":400,
               "hammer":400,
               "spear":400,
               "whip":400,
               "parry":400,
               "dagger":400,
               "staff":400,
               "dagger":400,
             ]),                                                    
]);

mapping base_skill_learned=([

"songjia_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),
"lifa_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),
"feima_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),
"duzun_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),
"dajiang_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),
"haisha_b":([
               "force":200,
               "dodge":200,
               "cuff":200,
               "blade":200,
               "sword":200,
               "strike":200,
               "finger":200,
               "leg":200,
               "hammer":200,
               "spear":200,
               "whip":200,
               "parry":200,
               "dagger":200,
               "staff":200,
               "dagger":200,
             ]),                                                    
]);


int doing_yanjiu(object ob,string skill,string org_name)
{
  
   ob->add_temp("yanjiu_times",1);
   if(ob->query_temp("yanjiu_times")>=20){
     base_skill_learned[org_name][skill]+=300*20;
     ob->add("potential",-300);
      
     if(base_skill_learned[org_name][skill]>=(base_skill[org_name][skill]+1)*(base_skill[org_name][skill]+1)){
     	base_skill_learned[org_name][skill]=0;
     	base_skill[org_name][skill]++;
     	tell_object(ob,"\n经过研究，"+get_board_shili(org_name)+"的"+to_chinese(skill)+"提高了！\n");
     }else
     tell_object(ob,"\n经过研究，"+get_board_shili(org_name)+"的"+to_chinese(skill)+"有了提高。\n");
     save();
     ob->start_busy(1);
     ob->delete_temp("yanjiu_times");
     ob->delete_temp("apply/short");
     message_vision("$N长嘘了口气，缓缓地站了起来。\n",ob);
     ob->save();
    
     return 0;
   }
   return 1;
}

int halt_yanjiu(object ob)
{
  ob->delete_temp("apply/short");
  ob->delete_temp("lingwu_times");
  message_vision("$N强行停止了研究。\n",ob);
  return 1;
}

int do_improve_skill(object ob,object where,string skill)
{
   object *teams;
   object sboard;
   int i,cost;
   string org_name,msg,temp_msg;
   
   org_name=where->query("shili/name");
   
   if(!(base_skill[org_name][skill]))
   return notify_fail("你无法研究"+skill+"。\n");
   
   sboard=load_object(BOARD_PATH+ob->query("shili/name"));
   
   teams=ob->query_team();
   if(teams)
   teams-=({0});
   
   if(sizeof(teams)>5)
   return notify_fail("一起研究武功的人数最多五人！\n");
   
   if(sizeof(teams)&&!ob->is_team_leader())
   return notify_fail("你不是队伍的首领！\n");
   
   if(sizeof(teams)){
     for(i=0;i<sizeof(teams);i++){
      
      if(teams[i]->is_fighting())
        return notify_fail(teams[i]->name()+"正在战斗中！\n");
      if(teams[i]->is_busy())
        return notify_fail(teams[i]->name()+"正忙着呢！\n");
      if(teams[i]->query("potential")<=0)
        return notify_fail(teams[i]->name()+"的潜能不够！\n");
      if(teams[i]->query("max_force")<3000)
        return notify_fail(teams[i]->name()+"的内力修为太低了，不能研究技能！\n");
      if(teams[i]->query("combat_exp")<800000)
        return notify_fail(teams[i]->name()+"的经验太低了，不能研究技能！\n");
      if(teams[i]->query("potential")<300)
        return notify_fail(teams[i]->name()+"的潜能不足，不能研究技能！\n");
        
      if(teams[i]->query_skill("literate",1)<200)
       return notify_fail(teams[i]->name()+"的读书识字太低了！\n");
      if(teams[i]->query_skill(skill,1)<200)
       return notify_fail(teams[i]->name()+"的"+to_chinese(skill)+"太低了！\n");
      if(teams[i]->query("shili/name")!=where->query("shili/name")&&
         !if_friend_org(teams[i],where) )
      return notify_fail(teams[i]->name()+"不是"+get_board_shili(where->query("shili/name"))+"一员，\n"+
                         "也不是"+get_board_shili(where->query("shili/name"))+"的结盟帮会成员！\n");      
      if(environment(teams[i])!=where)
      return notify_fail(teams[i]->name()+"和你们不在一起！\n");
     }
   }else{
     
     if(ob->is_fighting())
        return notify_fail("你正在战斗中！\n");
      if(ob->is_busy())
        return notify_fail("你正忙着呢！\n");
     if(ob->query("potential")<=0)
        return notify_fail("你的潜能不够！\n");
     if(ob->query("max_force")<3000)
        return notify_fail("你的内力修为太低了，不能研究技能！\n");
     if(ob->query("combat_exp")<800000)
        return notify_fail("你的经验太低了，不能研究技能！\n");
      if(ob->query("potential")<300)
        return notify_fail("你的潜能不足，不能研究技能！\n");
           
     if(ob->query_skill("literate",1)<200)
      return notify_fail("你的读书识字太低了！\n");
     if(ob->query_skill(skill,1)<200)
       return notify_fail("你的"+to_chinese(skill)+"太低了！\n");
     if(ob->query("shili/name")!=where->query("shili/name")&&
         !if_friend_org(ob,where) )
     return notify_fail("你不是"+get_board_shili(where->query("shili/name"))+"一员，\n"+
                         "也不是"+get_board_shili(where->query("shili/name"))+"的结盟帮会成员！\n");
    
  }
     
  if(sizeof(teams)){
   cost=100-sizeof(teams)*5;
   if(sboard->query("exp")<cost)
   return notify_fail("帮会储备经验不够了，无法继续研究基本技能！\n");
  }
  else{
   cost=100;
   if(sboard->query("exp")<100)
   return notify_fail("帮会储备经验不够了，无法继续研究基本技能！\n");
  }
  sboard->add("exp",-cost);
  if(sboard->query("exp")<0)
    sboard->set("exp",0);
  sboard->save();
   
  msg="$N盘膝而坐，默默地研究"+to_chinese(skill)+"";
  ob->set_temp("yanjiu_times",0);
  if(sizeof(teams)){
   for(i=0;i<sizeof(teams);i++)
    if(!teams[i]->is_busy()){
     temp_msg=replace_string(msg,"$N",teams[i]->name());
     teams[i]->set_temp("apply/short",({ temp_msg }) );
     message_vision("$N盘膝做下，开始研究"+to_chinese(skill)+"。\n",teams[i]);
     teams[i]->start_busy((:doing_yanjiu,teams[i],skill,org_name:),(:halt_yanjiu,teams[i]:) );
    }
  }
  else{
   temp_msg=replace_string(msg,"$N",ob->name());
   ob->set_temp("apply/short",({ temp_msg }) );
   message_vision("$N盘膝做下，开始研究"+to_chinese(skill)+"。\n",ob);
   ob->start_busy((:doing_yanjiu,ob,skill,org_name:),(:halt_yanjiu,ob:) );
  }
  
  return 1;
}

int check_skills(object ob,object where)
{
  string org_name;
  string *skills,*leaned_skills,msg;
  int i;
  
  org_name=where->query("shili/name");
  
  if(ob->query("shili/name")!=where->query("shili/name")&&
         !if_friend_org(ob,where)&&!wizardp(ob) )
  return notify_fail("你不是"+get_board_shili(where->query("shili/name"))+"一员，\n"+
                         "也不是"+get_board_shili(where->query("shili/name"))+"的结盟帮会成员！\n"); 
  
  skills=keys(base_skill[org_name]);
  leaned_skills=keys(base_skill_learned[org_name]);
  msg="\n\n"+get_board_shili(where->query("shili/name"))+"目前所研究的技能：\n\n";
  skills=sort_array(skills,(:strcmp:));
  for(i=0;i<sizeof(skills);i++){
    if(ob->query("env/skill_list"))
    msg+=sprintf("%s%-30s%3d/%3d%s\n",to_chinese(skills[i]),"("+skills[i]+")",
         base_skill[org_name][skills[i]],
         base_skill_learned[org_name][skills[i]]*100/( (base_skill[org_name][skills[i]]+1)*(base_skill[org_name][skills[i]]+1) ),
         "%");
    else
    msg+=sprintf("%s%-30s%3d/%3d\n",to_chinese(skills[i]),"("+skills[i]+")",
         base_skill[org_name][skills[i]],
         base_skill_learned[org_name][skills[i]]);
  }
  msg+="\n";
  ob->start_more(msg);
  return 1;
}

int if_get_upper(object ob,string skill)
{
  string org_name;
  
  org_name=ob->query("shili/name");
  
  if(base_skill[org_name][skill]<ob->query_skill(skill,1))
  return 0;
  return 1;
}
