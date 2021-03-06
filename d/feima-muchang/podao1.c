
#include <ansi.h>
inherit ROOM;

int do_yell();
void create ()
{
  set ("short","宽敞坡道");
  set ("long", @LONG
这里是个宽敞的坡道，这里已经是飞马牧场的外堡了。南边是飞马
牧场的吊桥。桥的下面满布尖头木头，若是掉下去就算神仙在世也是无
能为力了。所以出入飞马牧场的人须靠吊桥通行，这里的确有一夫当关，
万夫难渡之势。你可以高声叫(yell)守卫来放下吊桥。
LONG);

  set("exits", ([ 
  
	  "northwest":__DIR__"podao2",
	
         ]));
  set("objects",([
	  __DIR__"npc/dizi":1,
	  ]));
  set("outdoors","feima");
  set("valid_startroom", 1);
  setup();
 
}
void init()
{
	add_action("do_yell","yell");
}

int do_yell()
{
    int beipan;object me;object where;
    object bridge;
	me=this_player();
	where=environment(me);
    if(where->query("eixts/out")) return notify_fail("吊桥已经放下来了!\n");
    bridge=load_object(__DIR__"bridge");
    if(bridge->query("exits/enter"))
    return notify_fail("吊桥已经放下来了!\n");
	call_out("do_bridge",5,where);
	message_vision("守卫冲着$N大声道:"+RANK_D->query_respect(me)+",等一下,我这就放下吊桥!\n",me);
	tell_object(where,"只听隆隆声音,吊桥正缓慢的放下来了.\n");
	return 1;
}

void do_bridge(object where)
{
    object bridge;
	bridge=load_object(__DIR__"bridge");
	tell_object(where,"只听哐当一声,吊桥已经放下来了!\n");
	tell_object(bridge,"只听哐当一声,吊桥已经放下来了!\n");
	where->set("exits/out",__DIR__"bridge");
	where->set("can_go",1);
	bridge->set("exits/enter",__DIR__"podao1");
	remove_call_out("do_bridge");
	call_out("do_close",20,where,bridge);
	return;
}

void do_close(object where,object bridge)
{
	tell_object(where,"只听隆隆声音,吊桥被拉上去了.\n");
	tell_object(bridge,"只听隆隆声音,吊桥被拉上去了.\n");
	where->delete("exits/out");
	where->delete("can_go");
	bridge->delete("exits/enter");
	remove_call_out("do_close");
	return;
}
