
inherit NPC;
#include <ansi.h>
void create()
{
   set_name("护卫",({ "hu wei","hu","wei"}) );
        set("gender", "男性" );
        set("age",28);
   set("long","他是杂货铺的护卫。\n");
   set("max_kee",300);
   set("max_gin",300);
   set("max_sen",300);
   set("combat_exp",200000);
   setup();
   carry_object(__DIR__"obj/mianfen");
}
void die()
{
  message_vision(HIR"$N泪眼汪汪地看了身旁的老板一眼：我如此为你拼命，你却还趴在那里睡觉！\n"NOR,this_object());
  return ::die();
}