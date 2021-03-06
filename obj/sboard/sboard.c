// sboard.c

#include <ansi.h>
#include <org.h>
#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

void setup()
{
	string loc;
	    if( stringp(loc = query("location")) )
		move(loc);
	set("no_get", 1);
	restore();
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
		notes = notes[BOARD_CAPACITY / 2 .. BOARD_CAPACITY];

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
		return notify_fail("指令格式：discard <编号>\n");
	notes = query("notes");
	if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
		return notify_fail("没有这个编号。\n");
	num--;
	if(!this_player()->query("shili")&&!valid_discard(this_player(),notes[num]["id"]))
	return notify_fail("没有加入帮会还敢来这里捣乱？？\n");
	mem_body=new(LOGIN_OB);
	if((string)mem_body->set("id",notes[num]["id"])!=notes[num]["id"])
	return notify_fail("不能设定ID！\n");
	if(!mem_body->restore())
	return notify_fail("没有这个玩家，或者他已经自杀，或者他被巫师杀档了。\n");
	body=LOGIN_D->make_body(mem_body);
	if(!body->restore()){
	destruct(mem_body);
	return notify_fail("帮会系统出错，请报告巫师！\n");}
	if(this_player()->query("shili/name")!=body->query("shili/name")
	&&!valid_discard(this_player(),notes[num]["id"])){
	clear_ob(mem_body,body);
	return notify_fail("喂，看清楚点，这是你的地盘吗？？\n");}
	if(!this_player()->query("shili/power")
	&&!valid_discard(this_player(),notes[num]["id"])){
	clear_ob(mem_body,body);
	return notify_fail("小喽罗还是不要干这种事的好！\n");}
	if(body->query("shili/power")&&
	this_player()->query("shili/power")>=body->query("shili/power")
	&&!valid_discard(this_player(),notes[num]["id"])){
	clear_ob(mem_body,body);
	return notify_fail("你无权让对方退帮！\n");}
	
	if(this_player()->query("shili/leader")&&
	this_player()->query("id")==notes[num]["id"]){
	clear_ob(mem_body,body);
	return notify_fail("帮主不能退帮，只能用power 让位。\n");}
	clear_ob(mem_body,body);
        member=find_player(notes[num]["id"]);
        if(objectp(member)&&member!=this_player())
         {
         CHANNEL_D->do_channel( this_object(), "rumor",
			sprintf("%s被%s赶出%s了。", 
			member->name(),this_player()->name(),ORG_D->get_board_shili(query("board_id"))));
         tell_object(member,"你被赶出帮派了！\n");
        }
        if(!objectp(member))
          CHANNEL_D->do_channel( this_object(), "rumor",
			sprintf("%s被%s赶出%s了。", 
			notes[num]["author"],this_player()->name(),ORG_D->get_board_shili(query("board_id"))));
	if(member==this_player())
	CHANNEL_D->do_channel( this_object(), "rumor",
			sprintf("%s主动退出%s了。", 
			this_player()->name(),ORG_D->get_shili(member)));
	if(this_player()->query("id")!=notes[num]["id"])
	write("将第 " + (num+1) + " 名人员赶出帮会....Ok。\n");
	if(objectp(member))
	member->delete("shili");
	notes = notes[0..num-1] + notes[num+1..<1];
	set("notes", notes);
	save();
	return 1;
}

int do_list(string arg)
{
	mapping *notes, last_read_time = 0;
	int num, i, last_time_read;
	string msg = "", myid;

	notes = query("notes");
	last_read_time = this_player()->query("board_last_read");
	myid = query("board_id");
	if ( !arg || sscanf(arg, "%d", num)!=1 || num < 1 ) num = 1;
	if ( arg == "new") {
		if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
			num = 1;
		else
			for(num = 1; num<=sizeof(notes); num++)
				if( notes[num-1]["time"] > last_read_time[myid] ) break;
	};

	if (num > sizeof(notes)) return notify_fail("没有您想看的人员。\n");
	if (mapp(last_read_time)) last_time_read = last_read_time[myid];
	for(i=num-1; i<sizeof(notes); i++) {
		msg += sprintf("%s[%2d]" NOR,
			notes[i]["time"] > last_time_read ? HIY: "",
			i+1);
		msg += (sprintf("     %-=36s %18s (%s)\n",
			notes[i]["title"], notes[i]["author"],
			ctime(notes[i]["time"])[0..15] ))[4..<0];
	}
	this_player()->start_more(msg);
	return 1;
}

int do_check()
{
	object me;int exp,money;
	me=this_player();
	if(me->query("shili/name")!=query("board_id")&&!wizardp(me))
	return notify_fail("只有本帮派的人有权查看此名单榜！\n");
	exp=query("exp");
	money=query("money");
	tell_object(me,sprintf("本势力现有存款"+MONEY_D->money_str(money)+"，经验%d点\n",exp));
	return 1;
}

int do_qu(string arg)
{
	int value;object me;int money;
	string type;string m_name;
	me=this_player();
	if(!arg||sscanf(arg,"%d %s",value,type)!=2)
	return notify_fail("你要取出多少钱？\n");
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
	if(exp>100000)
	return notify_fail("一次最多奖励100000\n");
	if(me->query("shili/name")!=ob->query("shili/name"))
	return notify_fail("你们不是一个势力，不能奖励！\n");
	bexp=query("exp");
	if(exp>bexp)
	return notify_fail("没有这么多的经验可以奖励！\n");
	ob->add("combat_exp",exp);
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
	return 1;
}

int do_history()
{
  object ob;string *msg;
  string file,result;int i;
  ob=this_player();
  if(!ob->query("shili")&&!wizardp(ob))
  return notify_fail("你没有加入任何帮会，无权来查看这里的历史！\n");
  if(ob->query("shili/name")!=query("board_id")&&!wizardp(ob))
  return notify_fail("这不是你们势力的英雄榜，你无权在这里查看！\n");
  file=read_file("/log/org/"+query("board_id"));
  if(!stringp(file))
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前没有什么历史记录。\n");
  msg=explode(file,"\n");
  if(sizeof(msg)==0)
  return notify_fail(ORG_D->get_board_shili(query("board_id"))+"目前没有什么历史记录。\n");
  result=ORG_D->get_board_shili(query("board_id"))+"记录\n";
  for(i=0;i<sizeof(msg);i++){
    result +=msg[i]+"\n";}
  ob->start_more(result);
  return 1;
}
  
  