
inherit ITEM;

#include <ansi.h>

void create()
{
   
   set_name(HIG"镜片"NOR,({"jing pian","pian"}));
   set_weight(1000);   
   set("unit", "个");
   set("no_save",1);
   set("long","这是一个没有经过识别（ＳＨＩＢＩＥ）的镜片，你还不知道它的用途。\n");
   set("dlev",(1+random(3))*50);//在 create 时确定 dlev
   set("value",400000);
   setup();
   
}

void init()
{
        add_action("do_shibie","shibie");
}

int do_shibie()
{
         
         int lev;
         int dlev;
         int dtype;
         int damage,strong;
         
         object me = this_player();    
         object iron = this_object();    
         
        if(me->query("vocation")!="铁匠")
        return notify_fail("你不是铁匠，不能识别此物品!\n");
        if(iron->query("no_shibie")==1)
                return notify_fail("这个镜片已经识别过了!\n");
        
        lev=(int)me->query_skill("duanzao-jishu",1);       
        dlev=query("dlev");
        if(lev<dlev){
         
          return notify_fail("你的锻造技术太低了，不足以识别该镜片！\n");
        }
        
        damage=dlev/50*15+random(10);
        strong=dlev/50*30+random(10);
        
        set("weapon/damage",damage);
        set("weapon/strong",strong);
                
        iron->set("long","这是一个镜片，它的功效指数是：\n伤害："+damage+"\n坚固："+strong+"。\n");
        iron->set("no_shibie",1);
        message_vision("$N将镜片细打量了一遍，终于知道了它的作用！\n",me);
        me->add("vocation_score",10);//加 10 太多了
        message_vision("$N的职业声望增加了。\n",me);

        return 1;
}


