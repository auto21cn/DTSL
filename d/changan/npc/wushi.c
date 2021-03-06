
inherit NPC;
string give_book();
string give_book2();
string give_book3();
string give_book4();

void create()
{
   set_name("武师",({ "wu shi","wu","shi" }) );
   set("gender", "男性" );
   set("age", 32);
   set("long", "这是威远镖局的武师，看起来威风凛凛。\n");
       
   set("combat_exp", 90000);
   set("str", 28);
   set("per", 23);
   set("attitude", "peaceful");
   set_skill("unarmed",70);
   set_skill("parry",70);
   set_skill("dodge",70);
   set_skill("force",70);
   set("max_force",200);
   set("force",200);
   set("inquiry",([
	   "基本招架":(:give_book:),
	   "基本拳法":(:give_book2:),
	   "基本匕法":(:give_book3:),
	   "基本杖法":(:give_book4:),
	   ]));
   setup();
   carry_object(__DIR__"obj/cloth")->wear();
  
}
string give_book()
{
	object me,ob,book;
	me=this_player();ob=this_object();
	if(me->query_skill("parry",1)>100)
		return "你的基本功夫很好了，我可没什么指点的了！\n";
	if(ob->query("get_book"))
		if(ob->query("get_book")==me->name())
			return "不是刚给你一本书吗？还在这里罗嗦什么？！\n";
		else return "我刚给了"+ob->query("get_book")+"一本《基本招架》，你去找他要吧！\n";
	book=new(__DIR__"obj/pbook");
	ob->set("get_book",me->name());
	tell_object(me,""+ob->name()+"给了你一本《基本招架》。\n");
	book->move(me);
	return ""+RANK_D->query_respect(me)+"还是好好学习再来吧！\n";
}
string give_book2()
{
	object me,ob,book;
	me=this_player();ob=this_object();
	if(me->query_skill("cuff",1)>100)
		return "你的基本功夫很好了，我可没什么指点的了！\n";
	if(ob->query("get_book2"))
		if(ob->query("get_book2")==me->name())
			return "不是刚给你一本书吗？还在这里罗嗦什么？！\n";
		else return "我刚给了"+ob->query("get_book2")+"一本《基本拳法》，你去找他要吧！\n";
	book=new(__DIR__"obj/cbook");
	ob->set("get_book2",me->name());
	tell_object(me,""+ob->name()+"给了你一本《基本拳法》。\n");
	book->move(me);
	return ""+RANK_D->query_respect(me)+"还是好好学习再来吧！\n";
}
string give_book3()
{
	object me,ob,book;
	me=this_player();
	ob=this_object();
	
	if(me->query_skill("dagger",1)>100)
		return "你的基本功夫很好了，我可没什么指点的了！\n";
	if(ob->query("get_book3"))
		if(ob->query("get_book3")==me->name())
			return "不是刚给你一本书吗？还在这里罗嗦什么？！\n";
		else return "我刚给了"+ob->query("get_book3")+"一本《基本匕法》，你去找他要吧！\n";
	book=new(__DIR__"obj/dbook");
	ob->set("get_book3",me->name());
	tell_object(me,""+ob->name()+"给了你一本《基本匕法》。\n");
	book->move(me);
	return ""+RANK_D->query_respect(me)+"还是好好学习再来吧！\n";
}
string give_book4()
{
	object me,ob,book;
	me=this_player();
	ob=this_object();
	
	if(me->query_skill("staff",1)>100)
		return "你的基本功夫很好了，我可没什么指点的了！\n";
	if(ob->query("get_book4"))
		if(ob->query("get_book4")==me->name())
			return "不是刚给你一本书吗？还在这里罗嗦什么？！\n";
		else return "我刚给了"+ob->query("get_book4")+"一本《基本杖法》，你去找他要吧！\n";
	book=new(__DIR__"obj/sbook");
	ob->set("get_book4",me->name());
	tell_object(me,""+ob->name()+"给了你一本《基本杖法》。\n");
	book->move(me);
	return ""+RANK_D->query_respect(me)+"还是好好学习再来吧！\n";
}