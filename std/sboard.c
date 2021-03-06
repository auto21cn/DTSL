// sboard.c

#include <ansi.h>
#include <org.h>
#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

#define LEV1 "民夫"
#define LEV2 "辎重兵"
#define LEV3 "步兵"
#define LEV4 "勇士兵"
#define LEV5 "奇兵"

#define LEV1_MONEY 500
#define LEV2_MONEY 500
#define LEV3_MONEY 500
#define LEV4_MONEY 500
#define LEV5_MONEY 500

#define LEV1_TRAIN 70
#define LEV2_TRAIN 70
#define LEV3_TRAIN 70
#define LEV4_TRAIN 70
#define LEV5_TRAIN 70

#define LEV1_SUPPLY 10
#define LEV2_SUPPLY 50
#define LEV3_SUPPLY 50
#define LEV4_SUPPLY 50
#define LEV5_SUPPLY 50

#define SMALL_CITY_TAX  15000
#define MIDDLE_CITY_TAX 20000
#define BIG_CITY_TAX    40000


void setup()
{
	string loc;
	    if( stringp(loc = query("location")) )
		move(loc);
	set("no_get", 1);
	
	
	restore();
	
        if(
	   query("board_id")=="haisha_b"||
	   query("board_id")=="feima_b"||
	   query("board_id")=="songjia_b"
	  )
	set("max_person",100000);
	else
	set("max_person",80000);
	
    delete("do_train");
    if(query("lev1_guard")<0) set("lev1_guard",0);
    if(query("lev2_guard")<0) set("lev2_guard",0);
    if(query("lev3_guard")<0) set("lev3_guard",0);
    if(query("lev4_guard")<0) set("lev4_guard",0);
    if(query("lev5_guard")<0) set("lev5_guard",0);
    
	set("person",query("max_person"));	
	set("guard_person",query("lev1_guard")*LEV1_SUPPLY+query("lev2_guard")*LEV2_SUPPLY+
        query("lev3_guard")*LEV3_SUPPLY+query("lev4_guard")*LEV4_SUPPLY+
        query("lev5_guard")*LEV5_SUPPLY);
   
}

void init()
{
	add_action("do_join", "join");//sample is: join yanyan,
	add_action("do_list", "list");//see the members .
	add_action("do_discard", "discard");//the leader can do it
	add_action("do_check","check");//check the exp and money.
	add_action("do_qu","qu");//get the money
	add_action("do_jiangli","jiangli");//jiangli the exp to member.
	add_action("do_appoint",({"appoint","renming"}));//appoint cmds.
	add_action("do_history","history");//check the banghui history
	add_action("do_jiemeng","jiemeng");//结盟/解盟。
	add_action("do_deposit",({"deposit","cun"}));
	
	add_action("do_zhubing","zhubing");
	add_action("do_chebing","chebing");
	add_action("do_train",({"train","lianbing"}));
	add_action("do_wuzhuang","wuzhuang");
	add_action("do_chubing","chubing");
	add_action("do_shoubing","shoubing");
	add_action("do_checkwar","checkwar");
}

string query_save_file()
{
	string id;

	if( !stringp(id = query("board_id")) ) return 0;
	return DATA_DIR + "sboard/" + id;
}

string short()
{
	mapping *notes;
	int i, unread, last_read_time;

	notes = query("notes");
	if( !pointerp(notes) || !sizeof(notes) )
		return ::short() + " [ 此帮会没有任何人员 ]";

        return sprintf("%s [ %d 名人员 ]", ::short(), sizeof(notes));
}

string long()
{
	return ::long() + @LONG
加入帮会（势力）的方法：
list                             : 查看此帮会人员。
join id                          : 加入帮会（要经过帮主的许可）
discard 将某成员开除本帮会       : 帮主命令。
check                            : 查看本帮的贮备情况
qu 从储备中取出钱                : 帮主命令。
jiangli 奖励帮会人员经验         : 帮主命令。
renming(appoint)                 : 给本帮人员任命职务。帮主命令
jiemeng                          : 和其他帮会结盟/解盟。帮主命令
LONG;
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note)
{
	mapping *notes;

	note["time"] = time();
	notes = query("notes");
	if( !pointerp(notes) || !sizeof(notes) )
		notes = ({ note });
	else
		notes += ({ note });

	// Truncate the notes if maximum capacity exceeded.
	if( sizeof(notes) > BOARD_CAPACITY )
	     set("capacity",sizeof(notes));

	set("notes", notes);
	save();
	note["msg"] = "来自 " + ::short() + "\n" ;
	me->set("shili/name",query("board_id"));
	me->set("shili/deadtimes",query("deadtimes"));
	tell_object(me, "恭喜你加入了新的帮会。\n");
	this_object()->set("shili/name",me->query("shili/name"));
	me->save();
	CHANNEL_D->do_channel(this_object(), "banghui",
			sprintf("欢迎%s加入了%s", 
			me->name(),ORG_D->get_shili(me)));
	CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("%s加入了%s", 
			me->name(),ORG_D->get_shili(me)));
	me->delete_temp("mark_join");
	this_object()->delete("shili");
	save();
	return;
}

int do_join(string arg)
{
	mapping note;

	if(!arg) return notify_fail("请指定加入的ID。\n");
	if(this_player()->query("shili/name")==query("board_id"))
	 return notify_fail("你已经加入了，开什么玩笑？！\n");
	if(this_player()->query_temp("mark_join")!=query("board_id")
	  &&this_player()->query("shili/leader")!=query("board_id"))
	 return notify_fail("没有帮主的许可，你不能加入此帮会！\n");
	if(this_player()->query("id")!=arg)
	 return notify_fail("你只能使用自己的ID！\n");
	note = allocate_mapping(4);
	note["title"] = arg;
	note["id"]=this_player()->query("id");
	note["author"] = this_player()->query("name") + "("+this_player()->query("id")+")";
	done_post(this_player(), note);
	return 1;
}
int valid_discard(object ob,string id)
{
  if( ob->query("shili/leader")!=query("board_id")
	&&wizhood(ob) != "(admin)" 
	&&wizhood(ob) != "(arch)"
	&&ob->query("id")!=id)
    return 0;
  return 1;
}
void clear_ob(object ob,object ob2)
{
  destruct(ob);
  destruct(ob2);
}

int do_discard(string arg)
{
	mapping *notes;object ob,*user;object mem_body,body;
	int num;int i;object member;

	if( !arg || sscanf(arg, "%d", num)!=1 )
		return notify_fail("指令格式：discard <人物编号>\n");
	notes = query("notes");
	if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
		return notify_fail("没有这个编号。\n");
	num--;
	
	return ORG_D->org_del_member(this_player(),this_object(),notes[num]["id"],notes[num]["author"],
                   notes,num);
	
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

string left(string str,int long)
{
	int space,len,i;
	string s,oldstr;
	s="";oldstr=str;
	str=no_color(str);
	len=strlen(str);
	space=(long-len);
	for(i=0;i<space;i++) s+=" ";
	return sprintf("%s%s",oldstr,s);
}

int do_list(string arg)
{
        mapping *notes;
        int num, i, on_line_id;
	string msg = "", myid;
    string head,end,online;

	notes = query("notes");
    num=sizeof(notes);
	myid = query("board_id");

if (num==0) return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前没有任何人员。\n");
     on_line_id=0;
     online="";
for(i=0; i<num; i++) {
		msg += sprintf("%s[%2d]" NOR,
                        HIY,
			i+1);
msg +=left(notes[i]["author"],36);
msg +="加入时间：「"+(sprintf("%s"+"」"+"\n",
			ctime(notes[i]["time"])[0..15] ))[4..<0];
if(objectp(find_player(notes[i]["title"]))){
on_line_id++;
online +=notes[i]["author"]+" ";
if(on_line_id%5==0)
online+="\n";}
	}
head="━━━━━━━━━━━━━━━━━━━━━━━━━━━┉━━━━━━━━\n"+
"目前"+ORG_D->get_board_shili(query("board_id"))+"共有"+
HIW+chinese_number(num)+NOR+"名人员，总计被PK次数为"+
HIR+chinese_number(query("deadtimes"))+NOR+"\n\n"+
"目前共有"+HIY+chinese_number(on_line_id)+NOR+"名"+
"成员在线上，分别为：\n"+online+"\n\n";
end="━━━━━━━━━━━━━━━━━━━━━━━━━━━┉━━━━━━━━\n";
msg=head+msg+end;
	this_player()->start_more(msg);
	return 1;
}

int do_check()
{
	object me;int exp,money;
	string msg;
	
	me=this_player();
	if(me->query("shili/name")!=query("board_id")&&!wizardp(me))
	return notify_fail("只有本帮派的人有权查看储备！\n");
	exp=query("exp");
	money=query("money");
	msg="\n"+ORG_D->get_board_shili(query("board_id"))+"现有存款：";
	if(money<=0)
	msg+="零";
	else
	msg+=MONEY_D->money_str(money);
	msg+="，经验：";
	if(exp<=0)
	msg+="零";
	else
	msg+=sprintf("%d",exp);
	msg+="。\n\n";
	tell_object(me,msg);
	return 1;
}

int do_qu(string arg)
{
	int value;object me;int money;
	string type;string m_name;
	me=this_player();
	if(!arg||sscanf(arg,"%d %s",value,type)!=2)
	return notify_fail("你要取出多少钱？\n");
	if(value<=0)
	return notify_fail("怎么，想捣乱吗？？\n");
	if(value>10000)
	return notify_fail("一次取那么多干什么？慢慢来吧！\n");
	if(me->query("shili/leader")!=query("board_id"))
	return notify_fail("只有首领可以在这里取钱！\n");
	money=query("money");
	if(type=="silver") value=value*100;
	else if(type=="gold") value=value*10000;
	if(value>money)
	return notify_fail("你们势力的存款没有那么多！\n");
	MONEY_D->pay_player(me,value);
	money=money-value;
	set("money",money);
	tell_object(me,"OK!\n");
	log_file("org/"+me->query("shili/name"),me->name()+""+
	"取出了"+MONEY_D->money_str(value)+"    "+ctime(time())+"\n");
	this_object()->save();
	return 1;
}

int do_jiangli(string arg)
{
	object me,ob;int exp;string name;
	int bexp;
	me=this_player();
	if(!arg||sscanf(arg,"%s %d",name,exp)!=2) 
	return notify_fail("你要奖励谁？\n");
	if(me->query("shili/leader")!=query("board_id"))
	return notify_fail("只有首领才可以奖励别人！\n");
	if(!objectp(ob=present(name,environment(me))))
	return notify_fail("这里没有这个人！\n");
	if(exp<=0)
	return notify_fail("怎么，想捣乱吗？？\n");
	if(exp>100000)
	return notify_fail("一次最多奖励100000点经验值。\n");
	if(me->query("shili/name")!=ob->query("shili/name"))
	return notify_fail("你们不是一个势力，不能奖励！\n");
        if(time()>ob->query("jiangli_inter_time")&&time()-ob->query("jiangli_inter_time")<3600*24)
        return notify_fail("你必须过24个小时才可以奖励他的经验。\n");
        if(exp>ob->query("famous")*50)
        return notify_fail("以他在江湖中的声望，还不足以一次奖励这么多经验。\n");
        if(exp+ob->query("reward_exp")>ob->query("famous")*100)
        return notify_fail("你只能再奖励"+ob->name()+HIY+
        (ob->query("famous")*100-ob->query("reward_exp"))+NOR"点经验！\n");
 
	bexp=query("exp");
	if(exp>bexp)
	return notify_fail("现在没有这么多的经验可以奖励！\n");
	ob->add("combat_exp",exp);
        ob->set("jiangli_inter_time",time());
        ob->add("reward_exp",exp);
	bexp=bexp-exp;
	set("exp",bexp);
	this_object()->set("shili/name",this_player()->query("shili/name"));
	CHANNEL_D->do_channel(this_object(), "banghui",
			sprintf("%s奖励了%s "+chinese_number(exp)+"点经验。", 
			this_player()->name(),ob->name()));
	message_vision("$N奖励了$n"+chinese_number(exp)+"点经验！\n",me,ob);
	this_object()->delete("shili");
	log_file("org/"+me->query("shili/name"),me->name()+""
	+"奖励了"+ob->name()+chinese_number(exp)+"点经验"+"     "+ctime(time())+"\n");
	this_object()->save();
	ob->save();
	return 1;
}

int do_history(string arg)
{
  object ob;string *msg;
  string file,result;int i;
  ob=this_player();
  
  if(!arg||
     (arg!="-r"&&arg!="-w")
    )
  return notify_fail("history -r:查看帮会储备分配历史。\n"+
                     "history -w:查看历届帮主。\n");
  
  if(!ob->query("shili")&&!wizardp(ob))
  return notify_fail("你没有加入任何帮会，无权来查看这里的历史！\n");
  if(ob->query("shili/name")!=query("board_id")&&!wizardp(ob))
  return notify_fail("这不是你们势力的英雄榜，你无权在这里查看！\n");
 
 if(arg=="-r"){
  file=read_file("/log/org/"+query("board_id"));
  if(!stringp(file))
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前没有什么历史记录。\n");
  msg=explode(file,"\n");
  if(sizeof(msg)==0)
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前没有什么历史记录。\n");
  result=ORG_D->get_board_shili(query("board_id"))+"记录\n\n";
  for(i=0;i<sizeof(msg);i++){
    result +=msg[i]+"\n";}
  ob->start_more(result);
  return 1;
 }else{
  file=read_file("/log/org/"+query("board_id")+"_bangzhu");
  if(!stringp(file))
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前的首领还不是玩家。\n");
  msg=explode(file,"\n");
  if(sizeof(msg)==0)
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前的首领还不是玩家。\n");
  result=ORG_D->get_board_shili(query("board_id"))+"历届首领情况：\n\n";
  for(i=0;i<sizeof(msg);i++){
    result +=msg[i]+"\n";}
  ob->start_more(result);
  return 1;
}  
 
}
  
  
int do_jiemeng(string arg)
{
  string name;
  object ob;
  
  ob=this_player();
  
  if(!arg||
     (sscanf(arg,"-y %s",name)!=1
      &&sscanf(arg,"-n %s",name)!=1
      &&arg!="-f")
    )
  return notify_fail("请使用 jiemeng -y 帮会名字 和某帮会结盟\n"+
                     "       jiemeng -n 帮会名字 和某帮会解盟\n"+
                     "       jiemeng -f 列出当前结盟的帮会名称。\n");
  
  if(!ob->query("shili"))
  return notify_fail("江湖小混混一边呆着去！\n");
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这不是你的地盘。\n");
  
  if(arg=="-f") return ORG_D->list_friend_org(ob);
  
  if(!ob->query("shili/leader"))
  return notify_fail("你不是"+ORG_D->get_board_shili(query("board_id"))+"首领，不能结盟/解盟。\n");
  if(name==ob->query("shili/name"))
  return notify_fail("自己和自己还用结盟/解盟吗？\n");    
  
  if(sscanf(arg,"-y %s",name)==1)
  return ORG_D->make_friend(ob,name);
  else
  return ORG_D->make_enemy(ob,name);
  
}

int do_deposit(string arg)
{
	int bv,amount;
	int damount;
	string type;
	object type_ob;
	
	if(!this_player()->query("shili"))
        return notify_fail("江湖小混混一边呆着去！\n");
        if(this_player()->query("shili/name")!=query("board_id"))
        return notify_fail("这不是你的地盘。\n");
  
        if( this_player()->is_busy() )
                return notify_fail("你的动作还没有完成，不能存钱。\n");
        if( !arg || sscanf(arg, "%d %s", amount, type)!=2 )
                return notify_fail("指令格式：deposit <数量> <货币种类>\n");
	if( amount <= 0)
		return notify_fail("指令格式：deposit <数量> <货币种类>\n");
	type_ob = present(type + "_money", this_player());
        if( !type_ob)          return notify_fail("你身上没有这种货币。\n");
        if( (int)type_ob->query_amount() < amount )
                return notify_fail("你身上没有那麽多" + type_ob->query("name") + "。\n");
        bv = type_ob->query("base_value");
        if( !bv ) return notify_fail("这种东西不值钱。\n");
	damount =query("money");
	damount += amount * bv;
	set("money", damount);
	type_ob->add_amount(-amount);
	message_vision(sprintf("$N存入了%s%s%s。\n",
	chinese_number(amount), type_ob->query("base_unit"), type_ob->query("name")), this_player());
	this_player()->start_busy(1);
	return 1;

}

/* 下面是 城市战争部分 */



int do_zhubing(string arg)
{
  object ob;
  object sboard;
  
  ob=this_player();
  
  if(ob->query("combat_exp")<300000)
   return notify_fail("只有经验达到了 300，000 才可以进行驻兵！\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
   
  if( (!ob->query("shili/power")||ob->query("shili/power")>4)
     &&!ob->query("shili/leader"))
  return notify_fail("以你的权利目前不能给"+HIY+ORG_D->get_shili(ob)+NOR+"驻兵！\n");
  
  sboard=load_object(BOARD_PATH+ob->query("shili/name"));
  
  if(!sboard)
  return notify_fail("帮会出了问题，请报告巫师！\n");
  
  if(!arg||(arg!=LEV1)
   )
  return notify_fail("请使用 zhubing "+LEV1+"。\n");
  
    if(sboard->query("money")<LEV1_MONEY)
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"现在没有这么多钱来驻兵！\n");
    
    if(query("guard_person")>=query("person"))
    return notify_fail("目前已经达到"+HIY+ORG_D->get_shili(ob)+NOR+"的人口上限了！\n");
        
    if(query("do_zhubing")>=5)
    return notify_fail("不能一次驻扎太多的民夫，你等一会吧！\n");
    
    add("do_zhubing",1);
    
    tell_object(ob,"你决定在"+HIY+ORG_D->get_shili(ob)+NOR+"驻扎一些兵力。\n");
    
    call_out("start_zhubing",180,ob->name(),ob->query("shili/name"),sboard);
            
    sboard->save();
  return 1;
  
}

void start_zhubing(string name,string org_name,object sboard)
{
  
  sboard->set("shili/name",org_name);
  CHANNEL_D->do_channel(sboard,"banghui",name+"在"+ORG_D->get_board_shili(query("board_id"))+"驻扎了一些"+LEV1+"！\n");
  
  sboard->add("money",-LEV1_MONEY);
  add("lev1_guard",1);
  add("guard_person",LEV1_SUPPLY);
  add("do_zhubing",-1);
  
  sboard->save();
  
}


int do_chebing(string arg)
{
  object ob;
  object sboard;
  
  ob=this_player();
  
  if(ob->query("combat_exp")<500000)
   return notify_fail("只有经验达到了 500，000 才可以进行撤兵！\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
 
  if( (!ob->query("shili/power")||ob->query("shili/power")>3)
     &&!ob->query("shili/leader"))
  return notify_fail("以你的权利目前不能给"+HIY+ORG_D->get_shili(ob)+NOR+"撤兵！\n");
  
  sboard=load_object(BOARD_PATH+ob->query("shili/name"));
  
  if(!sboard)
  return notify_fail("帮会出了问题，请报告巫师！\n");
  
  if(!arg||
   (arg!=LEV1&&arg!=LEV2&&arg!=LEV3&&arg!=LEV4&&arg!=LEV5)
   )
  return notify_fail("请使用 chebing "+LEV1+"/"+LEV2+"/"+LEV3+"/"+LEV4+"/"+LEV5+"。\n");
  
  if(arg==LEV1){
    
    if(query("lev1_guard")<=0)
    return notify_fail( ORG_D->get_shili(ob)+"没有驻扎"+LEV1+"！\n");
    sboard->set("shili/name",ob->query("shili/name"));
    CHANNEL_D->do_channel(sboard,"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"撤消了一些"+LEV1+"！\n");
    sboard->add("money",LEV1_MONEY/3);
    add("lev1_guard",-1);
    add("guard_person",-LEV1_SUPPLY);
    save();
    
  }
  if(arg==LEV2){
    if(query("lev2_guard")<=0)
    return notify_fail( ORG_D->get_shili(ob)+"没有驻扎"+LEV2+"！\n");
    sboard->set("shili/name",ob->query("shili/name"));
    CHANNEL_D->do_channel(sboard,"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"撤消了一些"+LEV2+"！\n");
    sboard->add("money",LEV2_MONEY/3);
    add("lev2_guard",-1);
    add("guard_person",-LEV2_SUPPLY);
    save();
    
  }
  if(arg==LEV3){
    if(query("lev3_guard")<=0)
    return notify_fail( ORG_D->get_shili(ob)+"没有驻扎"+LEV3+"！\n");
    sboard->set("shili/name",ob->query("shili/name"));
    CHANNEL_D->do_channel(sboard,"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"撤消了一些"+LEV3+"！\n");
    sboard->add("money",LEV3_MONEY/3);
    add("lev3_guard",-1);
    add("guard_person",-LEV3_SUPPLY);
    save();
    
  }
  if(arg==LEV4){
    if(query("lev4_guard")<=0)
    return notify_fail( ORG_D->get_shili(ob)+"没有驻扎"+LEV4+"！\n");
    sboard->set("shili/name",ob->query("shili/name"));
    CHANNEL_D->do_channel(sboard,"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"撤消了一些"+LEV4+"！\n");
    sboard->add("money",LEV4_MONEY/3);
    add("lev4_guard",-1);
    add("guard_person",-LEV4_SUPPLY);
    save();
    
  }
  if(arg==LEV5){
    if(query("lev5_guard")<=0)
    return notify_fail( ORG_D->get_shili(ob)+"没有驻扎"+LEV5+"！\n");
    sboard->set("shili/name",ob->query("shili/name"));
    CHANNEL_D->do_channel(sboard,"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"撤消了一些"+LEV5+"！\n");
    sboard->add("money",LEV5_MONEY/3);
    add("lev5_guard",-1);
    add("guard_person",-LEV5_SUPPLY);
    save();
    
  }
  sboard->save();
  return 1;
  
}


int do_train(string arg)
{
  object ob;
  object sboard;
  int num;
  
  ob=this_player();
  
  if(ob->query("combat_exp")<500000)
   return notify_fail("只有经验达到了 500，000 才可以进行练兵！\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
  
  if(!ob->query_skill("qianjun-shu",1))
   return notify_fail("你必须学会「千军术」才可以练习士兵！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
  
  if( (!ob->query("shili/power")||ob->query("shili/power")>2)
     &&!ob->query("shili/leader"))
  return notify_fail("以你的权利目前不能给"+HIY+ORG_D->get_shili(ob)+NOR+"训练军队！\n");
  
  if(ob->query("vocation")!="杀手")
  return notify_fail("只有杀手可以训练士兵！\n");
  
  if(query("do_train")>=5)
   return notify_fail("已经有太多人练兵，可怜可怜民夫吧！\n");
  
  if(ob->query_temp("start_do_train"))
  return notify_fail("你正在训练士兵！\n");
  
  sboard=load_object(BOARD_PATH+ob->query("shili/name"));
  
  if(!sboard)
  return notify_fail("帮会出了问题，请报告巫师！\n");
  
  if(!arg||
     (arg!=LEV2&&arg!=LEV3&&arg!=LEV4&&arg!=LEV5)
    )
  return notify_fail("你要训练哪一类士兵？"+LEV2+" "+LEV3+" "+LEV4+" "+LEV5+"。\n");    
    
  if(arg==LEV2){
    if(!query("lev1_guard"))
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"还没有驻扎"+LEV1+"。\n");
    if(sboard->query("money")<LEV2_TRAIN)
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"现在没有这么多钱来训练"+LEV2+"！\n");
     
     tell_object(ob,"\n你开始训练士兵！\n");
     ob->set_temp("start_do_train",1);
     add("do_train",1);
     call_out("start_train",1,ob,sboard,LEV2,1,environment(ob),LEV2_TRAIN);
     return 1;
  }
  else
  if(arg==LEV3){
    if(!query("lev1_guard"))
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"还没有驻扎"+LEV1+"。\n");
    if(sboard->query("money")<LEV3_TRAIN)
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"现在没有这么多钱来训练"+LEV3+"！\n");
     
     tell_object(ob,"\n你开始训练士兵！\n");
     ob->set_temp("start_do_train",1);
     add("do_train",1);
     call_out("start_train",1,ob,sboard,LEV3,1,environment(ob),LEV3_TRAIN);
     return 1;
  }
  else
  if(arg==LEV4){
    if(!query("lev1_guard"))
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"还没有驻扎"+LEV1+"。\n");
    if(sboard->query("money")<LEV4_TRAIN)
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"现在没有这么多钱来训练"+LEV4+"！\n");
     
     tell_object(ob,"\n你开始训练士兵！\n");
     ob->set_temp("start_do_train",1);
     add("do_train",1);
     call_out("start_train",1,ob,sboard,LEV4,1,environment(ob),LEV4_TRAIN);
     return 1;
  }
  else
  if(arg==LEV5){
    if(!query("lev1_guard"))
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"还没有驻扎"+LEV1+"。\n");
    if(sboard->query("money")<LEV5_TRAIN)
     return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"现在没有这么多钱来训练"+LEV5+"！\n");
     
     tell_object(ob,"\n你开始训练士兵！\n");
     ob->set_temp("start_do_train",1);
     add("do_train",1);
     call_out("start_train",1,ob,sboard,LEV5,1,environment(ob),LEV5_TRAIN);
     return 1;
  }
  
  return 1;
 
}

void start_train(object ob,object sboard,string level,int times,object where,int cost)
{
   if(!ob){
     add("do_train",-1);
     return;
   }
   if(query("lev1_guard")<=0){
   		tell_object(ob,"由于民兵太少，已经无法再增加兵力了，你停止了练兵。\n");
   		ob->delete_temp("start_do_train");
     	add("do_train",-1);
     	return;
   }		
   if(environment(ob)!=where){
     tell_object(ob,"你结束了练兵！\n");
     ob->delete_temp("start_do_train");
     add("do_train",-1);
     return;
   }
   
   if(times>=30){
     tell_object(ob,"\n你让士兵们停下来，休息一下。\n");
     ob->delete_temp("start_do_train");
     add("do_train",-1);
     return;
   }
   
   if(!objectp(sboard))
     sboard=load_object(BOARD_PATH+ob->query("shili/name"));
   
   if(!objectp(sboard)){
      tell_object(ob,"帮会练兵出错，请报告巫师。\n");
      return;
   }
   
   if(sboard->query("money")<cost){
     tell_object(ob,HIY"\n你们帮会的储备不够了！\n"NOR);
     ob->delete_temp("start_do_train");
     add("do_train",-1);
     return;
   }
   
   if(ob->query("gin")<=50){
    tell_object(ob,HIR"\n你筋疲力尽，决定停下来休息一下。\n"NOR);
     ob->delete_temp("start_do_train");
     add("do_train",-1);
     return;
   }
   
   ob->receive_damage("gin",50);
   
   if(level==LEV2){
     add("lev2_guard_trains",1+ob->query_skill("qianjun-shu",1)/10);
     sboard->add("money",-cost);
     if(query("lev2_guard_trains")>=3000){
      
      if(query("guard_person")-LEV1_SUPPLY+LEV2_SUPPLY>query("person")){
        tell_object(ob,"你该继续提高"+HIY+ORG_D->get_shili(ob)+NOR+"的人口了！\n");
        return;
      }
      if(query("lev2_guard")<query("apply/armor")/3){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的装甲了！\n");
       return;
      }
      if(query("lev2_guard")<query("apply/damage")/2){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的武器装备了！\n");
       return;
      }
     CHANNEL_D->do_channel(this_object(),"rumor","据说"+ORG_D->get_shili(ob)+"的"+level+"增强了！\n");
     add("lev2_guard",1);
     add("lev1_guard",-1);
     add("guard_person",-LEV1_SUPPLY+LEV2_SUPPLY);
     set("lev2_guard_trains",0);
    }
    call_out("start_train",1,ob,sboard,level,times+1,where,cost);
    return;
  }
  
  if(level==LEV3){
     add("lev3_guard_trains",1+ob->query_skill("qianjun-shu",1)/10);
     sboard->add("money",-cost);
     if(query("lev3_guard_trains")>=3000){
      
      if(query("guard_person")-LEV1_SUPPLY+LEV3_SUPPLY>query("person")){
        tell_object(ob,"你该继续提高"+HIY+ORG_D->get_shili(ob)+NOR+"的人口了！\n");
        return;
      }
      if(query("lev3_guard")<query("apply/armor")/3){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的装甲了！\n");
       return;
      }
      if(query("lev3_guard")<query("apply/damage")/2){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的武器装备了！\n");
       return;
      }
     CHANNEL_D->do_channel(this_object(),"rumor","据说"+ORG_D->get_shili(ob)+"的"+level+"增强了！\n");
     add("lev3_guard",1);
     add("lev1_guard",-1);
     add("guard_person",-LEV1_SUPPLY+LEV3_SUPPLY);
     set("lev3_guard_trains",0);
    }
    call_out("start_train",1,ob,sboard,level,times+1,where,cost);
    return;
  }
 
 if(level==LEV4){
     add("lev4_guard_trains",1+ob->query_skill("qianjun-shu",1)/10);
     sboard->add("money",-cost);
     if(query("lev4_guard_trains")>=3000){
      
      if(query("guard_person")-LEV1_SUPPLY+LEV4_SUPPLY>query("person")){
        tell_object(ob,"你该继续提高"+HIY+ORG_D->get_shili(ob)+NOR+"的人口了！\n");
        return;
      }
      if(query("lev4_guard")<query("apply/armor")/3){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的装甲了！\n");
       return;
      }
      if(query("lev4_guard")<query("apply/damage")/2){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的武器装备了！\n");
       return;
      }
     CHANNEL_D->do_channel(this_object(),"rumor","据说"+ORG_D->get_shili(ob)+"的"+level+"增强了！\n");
     add("lev4_guard",1);
     add("lev1_guard",-1);
     add("guard_person",-LEV1_SUPPLY+LEV4_SUPPLY);
     set("lev4_guard_trains",0);
    }
    call_out("start_train",1,ob,sboard,level,times+1,where,cost);
    return;
  }     
  
  if(level==LEV5){
     add("lev5_guard_trains",1+ob->query_skill("qianjun-shu",1)/10);
     sboard->add("money",-cost);
     if(query("lev5_guard_trains")>=3000){
      
      if(query("guard_person")-LEV1_SUPPLY+LEV5_SUPPLY>query("person")){
        tell_object(ob,"你该继续提高"+HIY+ORG_D->get_shili(ob)+NOR+"的人口了！\n");
        return;
      }
      if(query("lev5_guard")<query("apply/armor")/3){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的装甲了！\n");
       return;
      }
      if(query("lev5_guard")<query("apply/damage")/2){
       tell_object(ob,"你该提高"+HIY+ORG_D->get_shili(ob)+NOR+"的武器装备了！\n");
       return;
      }
     CHANNEL_D->do_channel(this_object(),"rumor","据说"+ORG_D->get_shili(ob)+"的"+level+"增强了！\n");
     add("lev5_guard",1);
     add("lev1_guard",-1);
     add("guard_person",-LEV1_SUPPLY+LEV5_SUPPLY);
     set("lev5_guard_trains",0);
    }
    call_out("start_train",1,ob,sboard,level,times+1,where,cost);
    return;
  }  
  
}


int do_wuzhuang(string arg)
{
   
  object ob,obj;
  
  
  ob=this_player();
  
  if(ob->query("combat_exp")<400000)
   return notify_fail("只有经验达到了 400，000 才可以进行武装！\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
  
  if(!ob->query_skill("junxie-xue",1))
  return notify_fail("你必须学了「军械学」才可以武装城市！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
  
  if( (!ob->query("shili/power")||ob->query("shili/power")>6)
     &&!ob->query("shili/leader"))
  return notify_fail("以你的权利目前不能武装"+HIY+ORG_D->get_shili(ob)+NOR+"的军队！\n");
  
  if(ob->query("vocation")!="铁匠")
  return notify_fail("只有铁匠才可以武装"+HIY+ORG_D->get_shili(ob)+NOR+"的军队！\n");
  
  if(!arg) return notify_fail("你要拿什么来增加军队的武装？\n");
  obj=present(arg,ob);
  if(!obj) return notify_fail("你身上没有这个东西！\n");
  
  if( obj->query("rumor")
    ||obj->query("no_save")
    ||obj->query("no_sell")
    ||obj->query("no_get")
    ||obj->query("no_give")
    ||obj->query("nogive_player")
    )
    return notify_fail("这个东西不能用来增加军队的武装！\n");
  
  if(!obj->query("armor_prop")&&!obj->query("weapon_prop"))
  return notify_fail("你只能用“盔甲”或“兵器”来增加军队的武装。\n");
  
  add("apply/armor",(obj->query("armor_prop/armor")/15)*ob->query_skill("junxie-xue",1)/200);
  add("apply/damage",(obj->query("weapon_prop/damage")/15)*ob->query_skill("junxie-xue",1)/200);
  
  if(obj->query("equipped"))
   obj->unequip();
  
  destruct(obj);
  
  save();
  
  set("shili/name",ob->query("shili/name"));
  set("channel_id",ORG_D->get_shili(ob));
  CHANNEL_D->do_channel(this_object(),"banghui",ob->name()+"增加了"+ORG_D->get_shili(ob)+"的军队武装！\n");
  set("shili/name",0);
  set("channel_id",0);
  
  return 1;

}    


int if_do_action(object ob,string type)
{
  
  if(type=="lev1") return 1;
  
  if(ob->query_skill("war-heal",1)&&
   type=="lev2")
  return 1;
  
  if(ob->query_skill("bafang-zhenfa",1)&&
   type=="lev3")
  return 1;
  
  if(ob->query_skill("liaoyuan-tianshu",1)&&
   type=="lev4")
  return 1;
  
  if(ob->query_skill("wuxing-qishu",1)&&
   type=="lev5")
  return 1;
  
  return 0;
  
}

int do_chubing(string arg)
{
  
  object ob,guard;
  int num,cost_type;
  string type,guard_type;
  
  
  ob=this_player();
  
  if(ob->query("combat_exp")<500000)
   return notify_fail("只有经验达到了 500，000 才可以进行出兵！\n");
  
  if(objectp(ob->query_temp("city_war_guard")))
  return notify_fail("你已经带兵了。\n");
  
  if(ob->query("pker"))
  return notify_fail("通缉犯老实点吧！\n");
  
  if(time()>ob->query("war_guard_busy")&&time()-ob->query("war_guard_busy")<60*20)
   return notify_fail("你不能连续带兵！\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
    
  if( (!ob->query("shili/power")||ob->query("shili/power")>2)
     &&!ob->query("shili/leader"))
  return notify_fail("以你的权利目前不能从"+HIY+ORG_D->get_shili(ob)+NOR+"出兵！\n");
  
  if(!arg||sscanf(arg,"%d %s",num,type)!=2)
  return notify_fail("你要出 多少 什么种类 的兵？chubing 数量 类型\n");
  
  if(num<=0||num>=100)
   return notify_fail("不要捣乱！！\n");
  if(type!=LEV1&&type!=LEV2&&type!=LEV3&&type!=LEV4&&type!=LEV5)
  return notify_fail("你要出什么类型的兵？"+LEV1+" "+LEV2+" "+LEV3+" "+LEV4+" "+LEV5+"\n");
  
  if(type==LEV1) guard_type="lev1";
  else
  if(type==LEV2) guard_type="lev2";
  else
  if(type==LEV3) guard_type="lev3";
  else
  if(type==LEV4) guard_type="lev4";
  else
  if(type==LEV5) guard_type="lev5";
  
  if(type==LEV1) cost_type=LEV1_SUPPLY;
  else
  if(type==LEV2) cost_type=LEV2_SUPPLY;
  else
  if(type==LEV3) cost_type=LEV3_SUPPLY;
  else
  if(type==LEV4) cost_type=LEV4_SUPPLY;
  else
  if(type==LEV5) cost_type=LEV5_SUPPLY;
  
  if(num>query(guard_type+"_guard"))
  return notify_fail(HIY+ORG_D->get_shili(ob)+NOR+"没有这么多的"+type+"。\n");
  
  if(!if_do_action(ob,guard_type))
  return notify_fail("你学的技能不能指挥此类士兵！\n");
  
  add(guard_type+"_guard",-num);
  add("guard_person",-num*cost_type);
  
  guard=new("/std/orgroom/npc/guard");
  guard->set_status(num,guard_type,query("apply/armor"),query("apply/damage"),query("board_id"));
  guard->set("zhongcheng_du",100);
  
  guard->add_temp("damage",ob->query_skill("bafang-zhenfa",1)/5);
  guard->add_temp("damage",ob->query_skill("liaoyuan-tianshu",1)/5);
  guard->add_temp("damage",ob->query_skill("wuxing-qishu",1)/5);
  
  guard->move(environment(ob));
  guard->check_owner(ob);
  guard->set("owner_ob",ob);
  ob->set_temp("city_war_guard",guard);
  ob->set("war_guard_busy",time());
  ob->set_temp("dtsl_job","war");
  
  save();
  
  set("shili/name",ob->query("shili/name"));
  set("channel_id",ORG_D->get_shili(ob));
  CHANNEL_D->do_channel(this_object(),"banghui",ob->name()+"从"+ORG_D->get_shili(ob)+"派出了"+
    chinese_number(num*cost_type)+"人的"+type+"！\n");
  set("shili/name",0);
  set("channel_id",0);
  
  CHANNEL_D->do_channel(this_object(),"rumor","据说"+ORG_D->get_shili(ob)+"派出了一些士兵！\n");
  
  return 1;
  
}  


int do_shoubing()
{
  
  object ob,guard;
  int cost_type;
  string guard_type;
  
  
  ob=this_player();
  
  if(!objectp(guard=ob->query_temp("city_war_guard")))
  return notify_fail("你没有带兵。\n");
  
  if(!ob->query("shili/name"))
   return notify_fail("江湖小混混少来这里胡闹！\n");
   
  if(ob->query("shili/name")!=query("board_id"))
  return notify_fail("这里不是你的帮会！\n");
 
  guard_type=guard->query("guard_type");
 
  if(guard_type=="lev1") cost_type=LEV1_SUPPLY;
  else
  if(guard_type=="lev2") cost_type=LEV2_SUPPLY;
  else
  if(guard_type=="lev3") cost_type=LEV3_SUPPLY;
  else
  if(guard_type=="lev4") cost_type=LEV4_SUPPLY;
  else
  if(guard_type=="lev5") cost_type=LEV5_SUPPLY;
  
  guard->set("number",guard->query("number")*COMBAT_D->status(guard,1)/100);
  
  if(query("guard_person")+cost_type*guard->query("number")>query("person"))
  return notify_fail("你必须先提高"+HIY+ORG_D->get_shili(ob)+NOR+"的人口。\n");
  
  add(guard_type+"_guard",guard->query("number"));
  add("guard_person",guard->query("number")*cost_type);
  
  ob->set_temp("city_war_guard",0);
  ob->delete_temp("dtsl_job");
  
  destruct(guard);
  
  save();
  
  set("shili/name",ob->query("shili/name"));
  set("channel_id",ORG_D->get_shili(ob));
  CHANNEL_D->do_channel(this_object(),"banghui",ob->name()+"将一些出征的士兵派回了"+ORG_D->get_shili(ob)+"！\n");
  set("shili/name",0);
  set("channel_id",0);
  
  return 1;
  
}  




int do_checkwar()
{
  object ob;
  string msg,org_msg;
  int flag=0;
  
  ob=this_player();
  
  if(!wizardp(ob)&&ob->query("shili/name")!=query("board_id")){
    if(!ob->query_skill("zhencha-shu",1))
    return notify_fail("这里不是你的帮会！\n");
    else
    flag=1;
  }
       
  org_msg=ORG_D->get_board_shili(query("board_id"));
  
  msg=HIY+org_msg+"目前治理情况：\n"NOR;
  msg+=HIY"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"NOR;
  msg+="人口上限："+chinese_number(query("max_person"))+"人\n";
  
  if(!flag)
  msg+="目前人口："+chinese_number(query("person"))+"人\n";
  else
  msg+="目前人口："+chinese_number(query("person")+random(200-ob->query_skill("zhencha-shu",1)))+"人\n";
  
  if(!flag)
  msg+="士兵人口："+chinese_number(query("guard_person"))+"人\n";
  else
  msg+="士兵人口："+chinese_number(query("guard_person")+random(200-ob->query_skill("zhencha-shu",1)))+"人\n";
    
  msg+=HIR"兵力：\n"NOR;
  if(!flag)
  msg+=LEV1+"："+chinese_number(query("lev1_guard"))+"人   "+"单位所占人口："+chinese_number(LEV1_SUPPLY)+"人\n";
  else
  msg+=LEV1+"："+chinese_number(query("lev1_guard")+random(200-ob->query_skill("zhencha-shu",1)))+
     "人   "+"单位所占人口："+chinese_number(LEV1_SUPPLY)+"人\n";

  if(!flag)
  msg+=LEV2+"："+chinese_number(query("lev2_guard"))+"人   "+"单位所占人口："+chinese_number(LEV2_SUPPLY)+"人\n";
  else
  msg+=LEV2+"："+chinese_number(query("lev2_guard")+random(200-ob->query_skill("zhencha-shu",1)))+
     "人   "+"单位所占人口："+chinese_number(LEV2_SUPPLY)+"人\n";  
  
  if(!flag)
  msg+=LEV3+"："+chinese_number(query("lev3_guard"))+"人   "+"单位所占人口："+chinese_number(LEV3_SUPPLY)+"人\n";
  else
  msg+=LEV3+"："+chinese_number(query("lev3_guard")+random(200-ob->query_skill("zhencha-shu",1)))+
     "人   "+"单位所占人口："+chinese_number(LEV3_SUPPLY)+"人\n";
  
  if(!flag)
  msg+=LEV4+"："+chinese_number(query("lev4_guard"))+"人   "+"单位所占人口："+chinese_number(LEV4_SUPPLY)+"人\n";
  else
  msg+=LEV4+"："+chinese_number(query("lev4_guard")+random(200-ob->query_skill("zhencha-shu",1)))+
     "人   "+"单位所占人口："+chinese_number(LEV4_SUPPLY)+"人\n";
  
  if(!flag)
  msg+=LEV5+"："+chinese_number(query("lev5_guard"))+"人   "+"单位所占人口："+chinese_number(LEV5_SUPPLY)+"人\n";
  else
    msg+=LEV5+"："+chinese_number(query("lev5_guard")+random(200-ob->query_skill("zhencha-shu",1)))+
    "人   "+"单位所占人口："+chinese_number(LEV5_SUPPLY)+"人\n";
 
  
  msg+=HIR"\n武装：\n"NOR;
  
  if(!flag)
  msg+="装甲："+chinese_number(query("apply/armor"))+"\n";
  else
  msg+="装甲："+chinese_number(query("apply/armor")+random(200-ob->query_skill("zhencha-shu",1)))+"\n";
  
  if(!flag)
msg+="武器："+chinese_number(query("apply/damage"))+"\n";
  else
msg+="武器："+chinese_number(query("apply/damage")+random(200-ob->query_skill("zhencha-shu",1)))+"\n";
  
  msg+=HIY"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"NOR;
  
  ob->start_more(msg);
  
  return 1;
}
