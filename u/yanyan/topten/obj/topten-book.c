//排行榜

#include <ansi.h>

inherit ITEM;

mapping *exp_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
        (["第6名":"空缺"]),(["第7名":"空缺"]),(["第8名":"空缺"]),(["第9名":"空缺"]),(["第10名":"空缺"]),
});
mapping *richman_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
        (["第6名":"空缺"]),(["第7名":"空缺"]),(["第8名":"空缺"]),(["第9名":"空缺"]),(["第10名":"空缺"]),
});
mapping *oldman_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
        (["第6名":"空缺"]),(["第7名":"空缺"]),(["第8名":"空缺"]),(["第9名":"空缺"]),(["第10名":"空缺"]),
});
mapping *force_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
});
mapping *literate_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
});
mapping *unarmed_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
});
mapping *dodge_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
});
mapping *thief_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *axe_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *blade_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *throwing_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *fork_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *hammer_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),(["第4名":"空缺"]),(["第5名":"空缺"]),
        (["第6名":"空缺"]),(["第7名":"空缺"]),(["第8名":"空缺"]),
});
mapping *staff_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *sword_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});
mapping *whip_topten = 
({
        (["第1名":"空缺"]),(["第2名":"空缺"]),(["第3名":"空缺"]),
});

string *whichpart =
({
        BLU"第一章    十大高手排行榜  --------------------  P1"NOR,
        BLU"第二章    十大富翁排行榜  --------------------  P2"NOR,
        BLU"第三章    十大寿星排行榜  --------------------  P3"NOR,
        BLU"第四章    五大内功高手  ----------------------  P4"NOR,
        BLU"第五章    五大文化名人  ----------------------  P5"NOR,
        BLU"第六章    天下神偷  --------------------------  P6"NOR,
        BLU"第七章    三板斧  ----------------------------  P7"NOR,
        BLU"第八章    神州刀客  --------------------------  P8"NOR,
        BLU"第九章    暗器名家  --------------------------  P9"NOR,
        BLU"第十章    神鞭  ------------------------------  P10"NOR,
        BLU"第十一章  杖客  ------------------------------  P11"NOR,
        BLU"第十二章  八大锤  ----------------------------  P12"NOR,
        BLU"第十三章  三剑客  ----------------------------  P13"NOR,
        BLU"第十四章  探海夜叉  --------------------------  P14"NOR,
        BLU"第十五章  神拳无敌  --------------------------  P15"NOR,
        BLU"第十六章  踏雪无痕  --------------------------  P16"NOR,
});
string printdate = NATURE_D->game_time();

void create()
{
        string id;
        int i,exp;

        set_name("江湖 排行榜", ({ "topten" }));
        set_weight(800);
        set("unit", "本");
        set("long","这是记载江湖排行情况的书。你可以用(READ)来查阅。\n");
        set("value", 1600);
        set("material", "paper");
}

void init()
{
        object ob,me=this_object();

        seteuid(getuid());
        if( ob = new("/obj/magic-rice") )
                if( (exp_topten=ob->query( "exp_topten" ))
                        &&(richman_topten=ob->query("richman_topten"))
                        &&(oldman_topten=ob->query("oldman_topten"))
                        &&(force_topten=ob->query("force_topten"))
                        &&(unarmed_topten=ob->query("unarmed_topten"))
                        &&(dodge_topten=ob->query("dodge_topten"))
                        &&(literate_topten=ob->query("literate_topten"))
                        &&(thief_topten=ob->query("thief_topten"))
                        &&(axe_topten=ob->query("axe_topten"))
                        &&(blade_topten=ob->query("blade_topten"))
                        &&(throwing_topten=ob->query("throwing_topten"))
                        &&(fork_topten=ob->query("fork_topten"))
                        &&(hammer_topten=ob->query("hammer_topten"))
                        &&(staff_topten=ob->query("staff_topten"))
                        &&(sword_topten=ob->query("sword_topten"))
                        &&(whip_topten=ob->query("whip_topten")) )
                        destruct( ob );
                else
                        write(CYN"\n江湖排行榜出现问题！请通知江湖执法。\n\n"NOR);
        else
                write(CYN"\n江湖排行榜出现问题！请通知江湖执法。\n\n"NOR);

        add_action("do_read", "read");
}

int do_read( string arg )
{
        int i;
        string si;
        string *c_short=({"空缺","空缺","空缺","空缺","空缺","空缺","空缺","空缺","空缺","空缺","空缺","空缺",});

        switch( arg )
        {
                case "topten":
                case "天龙八部排行榜":
                        write( "你翻开《江湖排行榜》，只见上面写着：\n" );
                        write( "--------------------------------------------------------\n" );
                        for( i = 0; i < sizeof(whichpart); i++ )
                                write( "    "+whichpart[i]+"\n" );
                        write( "--------------------------------------------------------\n" );
                        write( "                          ----"+printdate+"出版\n" );
                        write( "你要阅读哪一章？\n" );
                        break;
                case "P1":
                case "p1":
                case "第一章":
                case "十大高手排行榜":
                        write( "你翻到第一章 『"+HIC"十大高手排行榜"NOR+"』，只见上面写着：\n" );
                        write( "当今武林十大高手排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 10; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( exp_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P2":
                case "p2":
                case "第二章":
                case "十大富翁排行榜":
                        write( "你翻到第一章 『"+HIC"十大富翁排行榜"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖十大富翁排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 10; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( richman_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P3":
                case "p3":
                case "第三章":
                case "十大寿星排行榜":
                        write( "你翻到第三章 『"+HIC"十大寿星排行榜"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖老寿星排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 10; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( oldman_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P4":
                case "p4":
                case "第四章":
                case "五大内功高手":
                        write( "你翻到第四章 『"+HIC"五大内功高手"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 5; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( force_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P5":
                case "p5":
                case "第五章":
                case "五大文化名人":
                        write( "你翻到第五章 『"+HIC"五大文化名人"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 5; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( literate_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P6":
                case "p6":
                case "第六章":
                case "天下神偷":
                        write( "你翻到第六章 『"+HIC"天下神偷"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( thief_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P7":
                case "p7":
                case "第七章":
                case "三板斧":
                        write( "你翻到第七章 『"+HIC"三板斧"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( axe_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P8":
                case "p8":
                case "第八章":
                case "神州刀客":
                        write( "你翻到第八章 『"+HIC"神州刀客"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( blade_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P9":
                case "p9":
                case "第九章":
                case "暗器名家":
                        write( "你翻到第九章 『"+HIC"暗器名家"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( throwing_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P10":
                case "p10":
                case "第十章":
                case "神鞭":
                        write( "你翻到第十章 『"+HIC"神鞭"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( whip_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P11":
                case "p11":
                case "第十一章":
                case "杖客":
                        write( "你翻到第十一章 『"+HIC"杖客"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( staff_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P12":
                case "p12":
                case "第十二章":
                case "八大锤":
                        write( "你翻到第十二章 『"+HIC"八大锤"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 8; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( hammer_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P13":
                case "p13":
                case "第十三章":
                case "三剑客":
                        write( "你翻到第十三章 『"+HIC"三剑客"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( sword_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P14":
                case "p14":
                case "第十四章":
                case "探海夜叉":
                        write( "你翻到第十四章 『"+HIC"探海夜叉"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 3; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( fork_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P15":
                case "p15":
                case "第十五章":
                case "神拳无敌":
                        write( "你翻到第十五章 『"+HIC"神拳无敌"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 5; i++ )

                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( unarmed_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
                case "P16":
                case "p16":
                case "第十六章":
                case "踏雪无痕":
                        write( "你翻到第十六章 『"+HIC"踏雪无痕"NOR+"』，只见上面写着：\n" );
                        write( "当今江湖排名如下：\n" );
                        write( "--------------------------------------------------------\n" );
                        si = "名次";
                        for ( i = 0; i < 5; i++ )
                        {
                                si = sprintf( "第%d名",i+1 );
                                sscanf( dodge_topten[i][si],"%*s\n%s\n%*d\n",c_short[i] );
                                write( "    "+HIY"第"+chinese_number(i+1)+"名  "NOR+c_short[i]+NOR"\n" );
                        }
                        write( "========================================================\n" );
                        break;
		   default:
                        return 0;
        }
        return 1;
}

