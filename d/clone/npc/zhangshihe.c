
inherit NPC;

void create()
{
   set_name("张士和",({ "zhang shihe","zhang"}) );
        set("gender", "男性" );
        set("age",42);
        set("long","他就是宇文化及的心腹张士和，据说\n"+
                   "他正在暗查江湖中流传的[长生诀]一事。\n");
        set("inquiry",([
         "长生诀":"你知道在哪里吗？知道就告诉我吧！\n",
         "宇文化及":"他是我的主子，我正在为他查找长生诀。\n",
         "石龙":"据说长生诀就在他的手中，想来不假！\n",
         "徐子陵":"哼，据说他是扬州最出名的扒手，我们正找他呢！\n",
         "寇仲":"哼，据说他是扬州最出名的扒手，我们正找他呢！\n",
         ]));
    setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}

