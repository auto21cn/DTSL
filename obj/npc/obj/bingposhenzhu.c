

#include <ansi.h>

inherit ITEM;


void create()
{
	set_name(HIG"冰魄"HIY"神珠"NOR, ({ "bingpo shenzhu" }) );
	set("unit", "个");
	set("long","这是一个冰魄神珠，据说可以克制长生诀的热内劲。\n");
	set("rumor",1);
	seteuid(getuid());
}

