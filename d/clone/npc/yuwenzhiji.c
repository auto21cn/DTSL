
inherit NPC;
#include <ansi.h>
void create()
{
   object *ob;
   set_name("�����Ǽ�",({ "yuwen zhijia","yuwen"}) );
        set("gender", "����" );
        set("age", 32);
   set("long","�������ķ��ĸ���֮һ�����Ļ������ֵ�,�峯������.");
   set("max_kee",2000);
   set("max_gin",2000);
   set("max_sen",2000);
   set("max_force",2000);
   set("force",2000);
   set("combat_exp",600000);
   set_skill("parry",160);
   set_skill("dodge",160);
   set_skill("force",160);
   set_skill("strike",160);
   set_skill("hanbing-zhang",160);
   set("jiali",100);
    setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}