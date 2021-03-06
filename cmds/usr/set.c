 
#define MAX_ENV_VARS   20
 
inherit F_CLEAN_UP;
 
int help();
 
int main(object me, string arg)
{
    int i;
    string term, *terms, *wiz_only, *allowed;
    mixed data;
    mapping env;
 
    wiz_only = ({"invisibility", "immortal","msg_min","msg_mout","msg_home","wiz_look"});
    allowed=({  "block_tell", "brief", "brief_message", "brief_all","yield","hanghui",
     "no_accept", "no_teach", "wimpy","kill_msg","no_story","skill_list","dazuo_msg",
     "tuna_msg","sandu"});
 
   if( me != this_player(1) ) return 0;
 
   env = me->query("env");
 
   if( !arg || arg=="" ) {
     write("你目前设定的环境变数有：\n");
     if( !mapp(env) || !sizeof(env) )
        write("\t没有设定任何环境变数。\n");
     else {
        terms = keys(env);
        for(i=0; i<sizeof(terms); i++)
          printf("%-20s  %O\n", terms[i], env[terms[i]]);
     }
     return 1;
   }
 
   if( sscanf(arg, "%s %s", term, data)!=2 ) {
     if(member_array(arg,allowed)==-1)
     	return help();
     term = arg;
     data = "YES";
   }
  if( term && term!="" ) {
     if( mapp(env) && undefinedp(env[term]) && sizeof(env) >= MAX_ENV_VARS )
        return notify_fail("你设的环境变数太多了，请先用 unset 删掉几个吧。\n");     
   if(member_array(term, allowed) == -1&&member_array(term,wiz_only)==-1)
        return help();
   if((wiz_level(me) == 0) && (member_array(term, wiz_only) != -1))
		return notify_fail("只有巫师能用这个设定。\n");

   if(term == "wimpy" && (sscanf(data, "%d", data)!=1||intp(data) < 0 || intp(data) > 80))  {
      return COMMAND_DIR"usr/wimpy"->help(me);
   }
    if(stringp(data)&&(strsrch(data,"/")!=-1||strsrch(data,"\\")!=-1))
    	return help();
    if(strlen(data)>80)
    	return notify_fail("你设定的字数太多了，请节省一些吧！\n");	

	me->set("env/" + term, data);
	printf("设定环境变数：%s = %O\n", term, data);
	return 1;
   }
   return help();
}
 
int help()
{
   write(@TEXT
指令格式：set <变数名> [<变数值>]
 
这个指令让你设定一些环境变数，不加参数时会显示你目前设定的环境变数，不指定
变数值，则内定值为 "YES"。
 
取消变数设定请用 unset 指令。
目前大唐双龙支持的环境变量为：
block_tell 不和其他人说话
brief      不显示房间描述 
no_accept  不接受别人物品
wimpy      设置战斗逃跑的最低范围
yield      打架不还手
kill_msg   设定打架时的描述。$N为自己，$n为对方
           如：$N朝$n喝道：今天不是你死就是我活！！
           支持颜色字符。参见 help nick
hanghui    不接收行会的信息。
no_story   不看大唐小品信息
skill_list 使用skills命令查看时，显示为百分数。
dazuo_msg  在经验达到 3M 以后，可以设定打坐时的描述
           如：$N闭上眼睛开始打坐
           支持颜色字符，参见 help nick
tuna_msg   在经验达到 3M 以后，可以设定吐纳时的描述
           如：$N闭上眼睛开始吐纳
           支持颜色字符，参见 help nick
sandu	   允许药师给你散毒
TEXT
   );
   return 1;
}
