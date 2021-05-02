
inherit ITEM;

int do_action(string arg);

void create()
{
   set_name("《刀诀》", ({ "dao jue","jue","bai_songque_linghui_book" }) );
   set_weight(100);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "本");
     set("nogive_player",1);
     set("no_drop",1);
     set("eff_times",3);
     set("long", "这是一本书，据说可以从中领会出东西来。\n");
   }
  
   setup();
}

void init()
{
  add_action("do_action","linghui");
}

int do_action(string arg)
{
   object ob;
   string msg;
   
   ob=this_player();
   
   if(!arg)
   return notify_fail("你要领会什么？\n");
   if(!id(arg))
   return notify_fail("这个东西不能领会！\n");
   
   if(random(100)<80){
      add("eff_times",-1);
      msg="$N冥思苦想，却丝毫领会不出什么来。\n";
      message_vision(msg,ob);
      if(query("eff_times")<=0){
      	ob->set("char_lev/bai_songque_fail",1);
      	ob->save();
      	destruct(this_object());
      	return 1;
      }
     return 1;
   }
    
   msg="$N看着上面的图画，突然灵机闪现，大叫一声：我领会到了！！\n";
   message_vision(msg,ob);
   ob->set("char_lev/bai_songque_ok",1);
   ob->save();
   destruct(this_object());
   return 1;
}