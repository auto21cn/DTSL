
inherit NPC;

void create()
{
   set_name("凌志高",({ "ling zhigao","ling"}) );
        set("gender", "男性" );
        set("age",31);
        set("nickname","双枪闯将");
        set("long","这就是海沙帮中的凌志高，他近来负责余航的事物。\n");
               
        set("combat_exp",250000);
        set_skill("parry",130);
        set_skill("dodge",130);
        set_skill("force",130);
        set_skill("spear",130);
        set_skill("normal-spear",130);
        set_skill("babu-ganchan",140);
        add_money("coin",20);
        set("shili/name","haisha_b");
    setup();
   carry_object(__DIR__"obj/cloth")->wear();
   carry_object(__DIR__"obj/spear")->wield();
  
}

