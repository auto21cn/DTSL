
inherit NPC;

void create()
{
   set_name("司马德勘",({ "sima dekan","sima","dekan" }) );
        set("gender", "男性" );
        set("age", 42);
        set("tetle","禁军统领");
   set("long", "他是隋朝的禁军统领,掌管皇帝的保卫工作。\n");
   set("combat_exp",600000);
   set("str", 28);
   set("per", 23);
   set("attitude", "peaceful");
   set_skill("unarmed",120);
   set_skill("dodge",120);
   set_skill("parry",120);
   set_skill("force",120);
   set_skill("spear",120);
   set_skill("cuff",120);
   set_skill("male-cuff",120);
   set_skill("levelone-qiang",120);
   set("max_gin",1500);
   set("max_sen",1500);
   set("max_kee",2000);
   set("force",2000);
   set("max_force",2000);
   setup();
   carry_object(__DIR__"obj/armor")->wear();
   carry_object(__DIR__"obj/guanxue")->wear();
   carry_object(__DIR__"obj/spear")->wield();
}

