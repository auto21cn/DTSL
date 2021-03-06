#include <ansi.h>

#define BOARD_CAPACITY query("capacity")

inherit F_DBASE;

string title=HIG"
    ※※※※※※※※※※※※※※※※※※※※※※※※※※
    ※                                                ※
    ※                   大唐双龙新闻                 ※
    ※                                                ※
    ※※※※※※※※※※※※※※※※※※※※※※※※※※
"+HIY+"    
    ━━━━━━━━━━━━━━━━━━━━━━━━━━
\n\n"NOR;

int main(object me,string arg)
{
	 object board;string msg;
        
         board=load_object("/obj/board/news_b");
	 if(!board) 
	 return notify_fail("新闻系统出错，请报告巫师！\n");
	 if(arg=="all"||arg=="new"){
	   msg=board->do_list_news(me,arg);
	   msg=title+msg;
           me->start_more(msg);
           return 1;
         }
         if(arg){
	   return board->do_read_news(arg);
	 }
        else{
         msg=board->tell_news(me);
         msg=title+msg;
        tell_object(me,"\n"+msg+"\n\n"+" 请使用news 数字 或 news next 来阅读新闻。\n\n");}
        return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : news all/数字
这个指令可以让你阅读大唐中发布的新闻。
使用news all 可以看到所有的新闻。
使用news new 可以看到新发布的新闻
使用news next 阅读下一个新闻
使用news 数字 可以阅读具体的新闻。
HELP
        );
        return 1;
}