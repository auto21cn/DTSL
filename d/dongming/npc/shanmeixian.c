
inherit	F_MASTER;
inherit NPC;
#include <ansi.h>
string do_quest();
string give_book();
int do_action1();

void create()
{
   int i;
   object *ob;
   
   set_name("单美仙",({ "shan meixian","shan","meixian" }) );
   set("gender", "女性" );
   set("nickname","东溟夫人");
   set("age",48);
   set("long", "这是东溟派的派主东溟夫人。\n");
       
    set("combat_exp",3000000);
   set("per", 26);
    set_skill("whip",300);
    set_skill("parry",300);
    set_skill("dodge",300);
    set_skill("force",300);
    set_skill("literate",300);
    set_skill("dongming-xinfa",300);
    set_skill("bihai-force",300);
    set_skill("shuiyun-xiufa",300);
    set_skill("strike",300);
    set_skill("nishang-piaoming",300);

    set("perform_quest/yanyu",1);
    set("apply_points",2000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: command("perform yanyu") :),
        (: command("exert shui") :),
        (: command("exert huo") :),
    }));

    set("max_gin",4000);
    set("max_sen",5000);
    set("max_kee",6000);
    set("max_force",8000);
    set("force",8000);
   create_family("东溟派",2,"掌门");
      
   set("inquiry",([
     "东溟战将":(:do_quest:),
     "水云袖法":(:do_action1:),
     //"基本锤法":(:give_book:),
     ]));
   setup();
   
   carry_object(__DIR__"obj/caiyi")->wear();
   
   ob=children(__DIR__"obj/baiyun-piao");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"你手中的"+ob[i]->query("name")+"被它的主人收回去了！\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"被一阵风卷走了。\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
   carry_object(__DIR__"obj/baiyun-piao")->wield();
  
}
void attempt_apprentice(object ob)
{   
	
	if(ob->query("family"))
	if(ob->query("family/family_name")=="东溟派")
	if((int)ob->query("family/generation",1)<=2)
	{   
	   command("say 此话从何说起？\n");
	   return;
	}
	
	if(ob->query("family"))
	if(ob->query("family/family_name")=="东溟派")
	if(ob->query("family/master_name")=="单琬晶"){
	  command("say 既然你已经拜了单琬晶为师，我就无法再收你为徒了！");
	  return;
	}
	
	if(ob->query("gender")=="男性"){
	
	command("say 我不收男弟子的！你如果诚心投入本派，去找尚仁吧！\n");
	return;
        }
        
        if(ob->query_skill("bihai-force",1)<150){
          command("say 碧海神功是我们东溟派的根基，你不好好学我怎么能收你为弟子呢？");
          return;
        }
        if(ob->query("office_number")<60){
        command("say 你的功绩这么低，我可不要这么懒惰的弟子！\n");
        return;
        }
            
	command("say 近来战乱纷起，我们东溟未必能置身事外，你可以要好好练习武艺，保护我们门派！\n");
	command("recruit "+ob->query("id"));
	return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "dongming3");
}
string do_quest()
{
  object ob,obj;
  
  ob=this_player();
  if(ob->query_skill("bihai-force",1)<200)
  return "你的功夫太低了，现在还无法超越的！\n";
  if(ob->query("family_lingwu")=="dongming")
  return "你已经是东溟战将了，还是去领悟提高自己的修为吧。\n";
  if(ob->query_temp("quest_fighter"))
  return "你还是快去战胜木人吧！\n";
  ob->set_temp("gage_shan",1);
  
  obj=new(__DIR__"q_shanmeixian");
  obj->set("name",ob->name()+"的木人");
  obj->set("target_id",ob->query("id"));
  obj->set_temp("owner_ob",ob);
  ob->set_temp("quest_fighter",obj);
  ob->add_temp_array("job_temp_killer",obj);
  
  obj->move(environment(ob));
  
   return "想成为东溟战将？要看看你有没有这个实力了，和这个木人打一下吧。\n";
}
/*
int surrender(object killer,object victim)
{
   object ob;
   if(!killer->query_temp("gage_shan"))
   return 1;
   message("vision",HIG"【东溟派】：东溟夫人纵声长啸：天下英雄听了，"+killer->name()+"已成为我派东溟战将\n"NOR,users());
   message_vision(HIC"$N微微一笑：没想到我东溟派还有你这样的后起之秀！\n"NOR,victim);
   message_vision(HIC"$N脸色突然严肃起来，轻声道：来，我告诉你一个本派的秘密！\n"NOR,victim); 
   tell_object(killer,"你来到东溟夫人身旁，东溟夫人道：本派有一个修炼东溟心法的地方，\n"+
                      "据说在海边的悬崖处。我一直没有找到，看你能不能找到，光大本派了！\n");
   killer->set("family_lingwu","dongming");
   killer->set("title","东溟战将");
   return 1;
}
int end_fight(object killer,object victim)
{
  if(!victim->query_temp("gage_shan"))
   return 1;
  message_vision("$N朝$n叹了口气，你还是回去再磨练磨练吧！\n",killer,victim);
  return 1;
}
*/
string give_book()
{
   object ob,book;
   
   ob=this_player();
   if(ob->query("family/family_name")!="东溟派")
   return "你不是东溟派弟子，和我说是没用的！\n";
   book=new(__DIR__"obj/book");
   book->move(ob);
   return "你拿着这本书好好地学习吧！\n";
}

int do_action1()
{
   object ob;
   
   ob=this_player();
   
   if(ob->query_skill("shuiyun-xiufa",1)<160){
    command("say 你的水云袖法修为太低了，现在还无法领会其中的诀窍！");
    return 1;
   }
   if(ob->query("perform_quest/duomeng")){
    command("say 你已经掌握了飘梦剑法的诀窍，无法再掌握水云袖法的诀窍！");
    return 1;
   }
   if(ob->query("perform_quest/yanyu")){
    command("say 你已经掌握了水云袖法的诀窍，以后自己去提高吧！");
    return 1;
   }
   if(ob->query("perform_quest/pili")){
    command("say 你已经掌握了雷霆锤法的诀窍，无法再掌握水云袖法的诀窍！");
    return 1;
   }
   
   ob->set_temp("perform_quest/yanyu_action1",1);
   command("say 当今天下袖法最厉害是我母亲阴后，此袖法是我看过后来到东溟自创的。");
   return 1;
}
