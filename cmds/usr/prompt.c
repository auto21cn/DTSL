// prompt.c
/* create by dsm@jianghu 99-8-20
   this is only for jianghu lib.
   via the feature message.c control prompt string.
*/
#include <ansi.h>
inherit F_MESSAGE;

string *clr_msg=({"$RED$","$GRN$","$YEL$","$BLU$","$MAG$","$CYN$","$WHT$","$NOR$",
		"$HIR$","$HIG$","$HIY$","$HIB$","$HIM$","$HIC$","$HIW$","$BLK$"
});
string *clr=({RED,GRN,YEL,BLU,MAG,CYN,WHT,NOR,
		HIR,HIG,HIY,HIB,HIM,HIC,HIW,BLK
});

string replace_color(string arg);
string un_replace_color(string arg);
int string_length(string arg);
int set_prompt(string yn,string arg,string mark);

int main(object me,string arg)
{
	string str;
	if(!arg){
		str=me->query("prompt");
		if(!str) return notify_fail("未设定提示符。\n");
		else write("当前的提示符是："+un_replace_color(str)+"\n"NOR);
		return 1;
	}
	if(arg=="NONE"){
		write("取消提示符设定。是否确定[Y/N]？");
		input_to("set_prompt","","delete");
		return 1;
	}
	if(string_length(arg)>20) return notify_fail("待设提示符太长。\n");
	str=replace_color(arg);
	write("新设定的提示符样式为：\n"+get_prompt(str)+NOR"\n"+"是否确定[Y/N]？");
	input_to("set_prompt",str,"set");
	return 1;
}
string replace_color(string arg)
{
	int i;
	for(i=0;i<sizeof(clr_msg);i++){
		arg=replace_string(arg,clr_msg[i],clr[i]);
	}
	return arg;
}
string un_replace_color(string arg)
{
	int i;
	for(i=0;i<sizeof(clr);i++){
		arg=replace_string(arg,clr[i],clr_msg[i]);
	}
	return arg;
}
int string_length(string arg)
{
	int i;
	for(i=0;i<sizeof(clr_msg);i++){
		arg=replace_string(arg,clr_msg[i],"");
	}
	i=strlen(arg);
	return i;
}
int set_prompt(string yn,string arg,string mark){
	if(yn!="Y" && yn!="y"){
		write("取消操作。\n");
		return 1;
	}
	switch(mark){
		case "set":this_player()->set("prompt",arg);break;
		case "delete":this_player()->delete("prompt");break;
		default:break;
	}
	return 1;
}
int help(object me)
{
   write( @HELP
指令格式: prompt		显示当前提示符。
          prompt &n		使用默认的第n种提示符。
          prompt text		显示一段文字（不超过20个字符）。

　　文字中可包含以下特殊字串。
$BLK$	黑色		$NOR$	恢复正常颜色
$RED$	红色		$HIR$	亮红色
$GRN$	绿色		$HIG$	亮绿色
$YEL$	土黄色		$HIY$	黄色
$BLU$	深蓝色		$HIB$	蓝色
$MAG$	浅紫色		$HIM$	粉红色
$CYN$	蓝绿色		$HIC$	天青色
$WHT$	浅灰色		$HIW$	白色

$JING$	当前的精神值	$QI$	当前的气血值
$TILI$	当前的体力值	

　　以下为巫师专用。
$DIR$	当前目录
HELP
   );
   return 1;
}
