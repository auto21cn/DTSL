//


inherit SKILL;

string query_type()
{
   return "literate";
}

int valid_learn(object me)
{
    if(me->query_skill("junxie-xue",1)>=me->query("max_pot")-100)
     return notify_fail("你的武学修为太低了，无法继续提高这个技能了！\n");
    
    if(me->query_skill("war-heal",1)||
       me->query_skill("bafang-zhenfa",1)||
       me->query_skill("liaoyuan-tianshu",1)||
       me->query_skill("wuxing-qishu",1)||
       me->query_skill("qianjun-shu",1)||
       me->query_skill("zhencha-shu",1)||
       me->query_skill("dadao-qishu",1)
      )
      return notify_fail("你的杂学太多了，还是专一学一门吧！\n");
    
    if(me->query("family/family_name")!="东溟派"){
      me->add("potential",-10);
      if(me->query("potential")<0)
       me->set("potential",0);
    }
    
    return 1;
}


string help_action()
{
write(@LONG
    军械学

    此技能可以让你装备城市的盔甲和兵器力量
    如果你是东溟派的弟子，则学起来要相对容易些。
        
LONG);
return "\n";
}

