
#include <room.h>

inherit ROOM;

#include <ansi.h>

int do_heal();

void create()
{
	set("short", "疗伤室");
	set("long", @LONG
这里是石龙武馆的疗伤室，凡是在武馆中的弟子因为练功而受了伤，
都可以到这里治疗。只见地上盘膝坐着几名弟子，头上冒出阵阵白烟，正
在那里运功疗伤。这里挂着一个牌子(pai)。
LONG
);


	set("exits", ([
		"west" :__DIR__"beilang2",
               
	]));
	
	set("item_desc",([
	   "pai":"你可以使用 liaoshang 来治疗伤口。\n",
	   ]));
	
	/*set("objects",([
	    __DIR__"npc/shoumen_dizi":1,
	    ]));*/
       set("no_fight",1);
       set("can_exercise",1);
       set("can_respirate",1);
       //set("outdoors", "slwg");
	setup();
}

void init()
{
   add_action("do_heal","liaoshang");
}

int do_healing(object me);
int do_halt(object me);

int do_heal()
{
   object ob;
   string str;
   
   ob=this_player();
   
   
   if(ob->query("eff_kee")==ob->query("max_kee")&&
	   ob->query("eff_gin")==ob->query("max_gin"))
   return notify_fail("你没受内伤，不用疗伤。\n");
   
   if(ob->is_busy())
   return notify_fail("你正忙着呢！\n");
    
   str=HIW"$N盘膝坐下，头上冒出阵阵白气。\n"NOR;
   
   message_vision(str,ob);
	str=replace_string(str,"$N",ob->name());
	str=replace_string(str,"\n","");
	ob->set_temp("apply/short",({str}));
   
   ob->start_busy((:do_healing:),(:do_halt:));
   return 1;
}

int do_healing(object ob)
{
   int cost;
   
   cost=ob->query_con();
     
   ob->receive_heal("kee",cost);
   ob->receive_curing("kee",cost);
   
   ob->receive_heal("gin",cost);
   ob->receive_curing("gin",cost);
   
   if(ob->query("eff_kee")==ob->query("max_kee")&&
   ob->query("eff_gin")==ob->query("max_gin"))
   { message_vision(HIW"$N长长地吐了一口气，站了起来。\n"NOR,ob);
     ob->delete_temp("apply/short");
     return 0;
    }
   return 1;
}

int do_halt(object ob)
{
  message_vision("$N将气息压回丹田，长舒了一口气，站了起来。\n",ob);
  ob->delete_temp("apply/short");
  return 1;
}
