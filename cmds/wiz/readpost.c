

inherit F_CLEAN_UP;

#define READ_BOARD_DIR "/obj/board/"

mapping board=([
"大江联留言版":"dajiang_b.c",
"独尊堡留言版":"duzun_b.c",
"飞马牧场留言版":"feima_b.c",
"宋家堡留言版":"songjia_b.c",
"海沙帮留言版":"haisha_b.c",
"天策府留言版":"lifa_b.c",
"静念禅门派院留言版":"party_cy_b.c",
"阴癸派门派留言版":"party_yg_b.c",
"慈航静门派斋留言版":"party_jz_b.c",
"弈剑派门派留言版":"party_yj_b.c",
"花间派门派留言般":"party_hj_b.c",
"突厥门派留言版":"party_tj_b.c",
"东溟派门派留言版":"party_dm_b.c",
"扬州客栈留言版":"pal_b.c",
"技能研究专栏":"skill_b.c",
"巫师留言版":"wiz_b.c",
]);

int do_help();

int main(object me, string arg)
{
   string *all_boards;
   int i;
   string item;
   string name;
   object ob;
   
   int num;
   mapping *notes, last_read_time;
   string myid;
   
   if(!arg) return do_help();
   if(sscanf(arg,"%s %s",name,item)!=2&&
    sscanf(arg,"%s",name)!=1)
   return notify_fail("请使用 readpost 留言版名字 第几个留言\n"+
                      "或 readpost 留言版名字  格式。\n");
   all_boards=keys(board);
   if(member_array(name,all_boards)==-1)
   return do_help();
   ob=load_object(READ_BOARD_DIR+board[name]);
   if(!ob)
   return notify_fail("这个留言版已经不存在，请查看其他留言版。\n");
   if(!(item)){
     me->start_more(ob->long());
     return 1;}
   
   last_read_time = this_player()->query("board_last_read");
   myid =ob->query("board_id");
   notes =ob->query("notes");
   if( !pointerp(notes) || !sizeof(notes) )
   return notify_fail("留言板上目前没有任何留言。\n");
   
   if( item=="new" || item=="next" ) {
		if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
			num = 1;
		else
			for(num = 1; num<=sizeof(notes); num++)
				if( notes[num-1]["time"] > last_read_time[myid] ) break;
			
	} else if( !sscanf(item, "%d", num) )
		return notify_fail("你要读第几张留言？\n");
  
   if( num < 1 || num > sizeof(notes) )
		return notify_fail("没有这张留言。\n");
	num--;
	me->start_more( sprintf(
"[%d] %-40s %s(%s)\n----------------------------------------------------------------------\n",
		num + 1, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9])
		+ notes[num]["msg"] );

	// Keep track which post we were reading last time.
	if( !mapp(last_read_time) )
		me->set("board_last_read", ([ myid: notes[num]["time"] ]) );
	else 
		if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
			last_read_time[myid] = notes[num]["time"];
   return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : readpost 留言版名字 
           readpost 留言版名字 第几张留言
           readpost 留言版名字 next
           readpost 留言版名字 new
         
         这条指令可以让你阅读大唐现有的留言版。
         使用 readpost 可以知道可以阅读的留言版。
         使用方法：
         如
         readpost 天策府留言版
         则是看 天策府留言版 所有的内容
         
         readpost 天策府留言版 1
         则是看 天策府留言版 第一条内容
         
         readpost 天策府留言版 next
         则是看 你没有看过的天策府留言版新的内容
         
         readpost 天策府留言版 new
         则是看 你没有看过的天策府留言版新的内容
         
         如果需要添加留言版个数，请修改 /cmds/wiz/readpost.c
         
                              真冰河(Yanyan)@大唐双龙
         
HELP
    );
    return 1;
}

int do_help()
{
  string *all_boards;
  string msg;
  object ob;
   int i;
   msg="目前可以阅读以下留言版：\n";
   ob=this_player();
  all_boards=keys(board);
  for(i=0;i<sizeof(all_boards);i++){
  	
    msg+=all_boards[i]+"\n";}
  ob->start_more(msg);
  return 1;
}