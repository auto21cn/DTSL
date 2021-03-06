
#include <ansi.h>
inherit ROOM;

int do_reg(string arg);

void create ()
{
  set ("short","毕业篇");
  set ("long", @LONG
恭喜你从大唐学院中毕业了！如果你觉得确实没有什么问题了，请
下楼 down 就可以了，如果你觉得还有问题，可以再回去看看。以后的
江湖生活将伴随着你，请随时使用 news 命令来查看游戏的更新情况。
对于巫师造成的错误，或导致的其他严重问题，请用 e-mail 的形式通
知，不要想着非等巫师上线再解决，因为巫师也有自己的工作，不可能
总是上线的。目前的 e-mail 可以为：realyanyan@sohu.com ，有什么
问题也请发信到这个e-mail。对于游戏本身 bug造成的损失，你有权利
向巫师取得补偿，这点千万不要担心！
*
如果不麻烦的话，你可以使用 register 命令来确定你的有效电子邮件，
以便于巫师及时与你取得联系，这个步骤不需要你退出游戏。
*
祝你在大唐双龙传玩得开心！
LONG);

  set("exits", ([ 
  "down":"/d/slwg/zoulang1",
 "south":__DIR__"room13",
        ]));
  
  
set("no_fight",1);
set("no_exert",1);
  set("valid_startroom", 1);
  setup();
 
}

void init()
{
  
  add_action("do_reg","register");
}

int do_reg(string arg)
{
   object ob,link_ob;
   
   ob=this_player();
   
   if(!arg)
    return notify_fail("请输入你的电子邮件地址。\n");
  
   if(strsrch(arg,"/")!=-1)
    return notify_fail("请输入正确的电子邮件地址。\n");
   
   if(strsrch(arg,"@")==-1)
    return notify_fail("请输入正确的电子邮件地址。\n");
   
   ob->set("email",arg);
   if(!objectp(link_ob=ob->query_temp("link_ob")))
    return notify_fail("出错，请报告巫师！\n");
  
     LOGIN_D->set_email(link_ob,arg);
 
   ob->save();
   
   tell_object(ob,"电子邮件确定完毕！今后巫师将通过这个电子邮件与你联系！\n");
   return 1;
}