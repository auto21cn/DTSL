
inherit NPC;

#include <ansi.h>
void create()
{
   set_name("宋玉致",({ "song yuzhi","song","yuzhi" }) );
   set("gender", "女性" );
   set("age", 22);
   set("long", "她就是宋家堡的宋玉致。\n");
       
   set("combat_exp", 300000);
   set("per", 27);
   set("gin",1000);
   set("max_gin",1000);
   set("kee",1000);
   set("max_kee",1000);
   set("sen",1000);
   set("max_sen",1000);
   set("force",1000);
   set("max_force",1000);
   set_skill("tiandao-bajue",100);
   set_skill("blade",100);
   set_skill("dodge",100);
   set_skill("parry",100);
   set_skill("unarmed",100);
   set_skill("cuff",100);
   set_skill("anxiang-fuying",100);
   set_skill("force",110);
   set_skill("tiangang-sanjue",100);
   set_skill("poyu-quan",100);  
   create_family("宋家堡",5,"门人");
   set("shili",([
      "name":"songjia_b",
      ]));
   
   set("inquiry",([
    "寇仲":"他一心称霸天下，和爹爹的心思不谋而和，我该怎么做呢？\n",
    "徐子陵":"他生性洒脱，可能去成都找石青璇了吧！\n",
    "宋缺":"他是家父，如今帮着寇仲称霸天下，唉！\n"
    ]));
   setup();
   carry_object(__DIR__"obj/chouyi")->wear();
   carry_object(__DIR__"obj/blade")->wield();
  
}


