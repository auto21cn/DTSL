
inherit NPC;

#include <ansi.h>

void create()
{
   set_name("翟让",({ "zhai rang","zhai"}) );
        set("gender", "男性" );
        set("age",35);
     	
   set("long", "翟让人称“大龙头”，乃瓦岗军的首领。\n");
       
   set("combat_exp", 800000);
   set("str", 30);
   set("per", 24);
   
   set_skill("strike",200);
   set_skill("dodge",200);
   set_skill("parry",200);
   set_skill("force",200);
   set_skill("cuff",200);
   
   set_skill("jiutian-huanzhang",200);

   set_skill("tianmo-huanzong",200);
   
   set("max_kee",2500);
   set("max_gin",2500);
   set("max_sen",2500);
   set("force",2500);
   set("max_force",2500);
   
   set("inquiry",([
        "沈落雁":"她可是我们瓦岗寨的头号军事！\n",
        "李密":"他乃我手下第一大将，有人说他要造反，我可要小心一些了。\n",
        "寇仲":"这种无名的角色我可没听说过。\n",
        "徐子陵":"这是什么人物？我可没听说过他的名号。\n",
        ]));
   
   setup();
  
}
