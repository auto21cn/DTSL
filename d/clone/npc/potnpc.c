#include <ansi.h>
inherit NPC;

#define SCORE_D "/adm/daemons/scored.c"

int check_pot();
int give_test_reward();

void create()
{
        set_name("天竺高僧",({ "gao seng","gao","seng"}) );
        set("gender", "男性" );
        set("class","bonze");
        set("long","这是位天竺高僧，据说功力不凡。\n");
        set("age", 32);
        set("inquiry",([       
        "潜能":(:check_pot:),
        "测试奖励":(:give_test_reward:),
        ]));
        
        set("target_id","####");
        
    setup();
    carry_object("/obj/cloth/seng-cloth")->wear();
  
}

void init()
{
  add_action("do_save_pot","savepot");
  add_action("do_get_pot","getpot");
}

int do_save_pot(string arg)
{
  object ob;
  int pot;
  
  ob=this_player();
  
  if(is_busy()){
    command("say 请等一下... ...");
    return 1;
  } 
  
  if(!arg){
    command("say 你想要保存多少潜能？\n");
    return 1;
  }
  
  
  pot=atoi(arg);
  if(pot<10||pot>100){
   command("say 一次最少保存 10 点潜能，最多保存 100 点潜能。");
   return 1;
  }
  if(pot>ob->query("potential")){
   command("say 你现在没有这么多潜能！");
   return 1;
  }
  if(ob->query("office_number")<(pot+ob->query("save_potential"))/20){
   command("say 1 点功绩可以保存 20 点潜能。你现在的功绩太少了！\n");
   return 1;
  }
  
  ob->add("potential",-pot);
  ob->add("save_potential",pot);
  
  start_busy(2);
  
  command("say 好，我已经给你保存了"+HIY+chinese_number(pot)+NOR+CYN+"点潜能！\n");
  return 1;
  
  
}

int do_get_pot(string arg)
{
  object ob;
  int pot;
  
  ob=this_player();
  
  if(is_busy()){
    command("say 请等一下... ...");
    return 1;
  } 
  
  if(!arg){
    command("say 你想要释放多少潜能？\n");
    return 1;
  }
  
  
  pot=atoi(arg);
  if(pot<=0||pot>100){
   command("say 以我的功力，每次只能给你释放一百点潜能！");
   return 1;
  }
  if(pot>ob->query("save_potential")){
   command("say 你现在没有保存这么多潜能！");
   return 1;
  }
 
  ob->add("save_potential",-pot);
  ob->add("potential",pot);
  
  start_busy(2);
  
  command("say 好，我已经给你释放了"+HIY+chinese_number(pot)+NOR+CYN+"点潜能！\n");
  return 1;
  
  
}

int check_pot()
{
  object ob;
  
  ob=this_player();
  
  if(ob->query("save_potential")){
   command("say 我已经给你存储了"+HIY+chinese_number(ob->query("save_potential"))+
     NOR+CYN+"点潜能！");
   return 1;
  }
  
  command("say 使用savepot来保存潜能，使用getpot来释放潜能。\n"+
          "每次存储潜能需要一定数量的功绩。\n");
  return 1;
  
}

/*
一、 特殊贡献奖励：xuer 
奖励原因：找出并报告了很多重要的BUG，并且发表了多篇关于DT建设的比较好的建议。 

二、 高级贡献奖励： 
llklhxxc leo caimi winner tott zhch miccire 

三、 中级贡献奖励 
hide issac forget ylei gest trsk sister hope yihe kitty lanse sjsega yuki mercuri over stopgab love zxmly yatina tiexue 

四、 初级贡献奖励 
pound xhx wish anything zax huanle lklk yuhe tianyi none miclon denis xing lazylong sea shashou strong anan zyf xuedao 

*/

string *reward_one=({
"xuer","leo"});

string *reward_two=({
"yuki","caimi","winner","tott","zhch","anan"});

string *reward_three=({
"hide","forget","ylei","gest","trsk","sister","hope","yihe","kitty","lanse", 
"sjsega","mercuri","over","stopgab","love","zxmly","yatina","tiexue","dagon", 
"jerry","tely","lklk","leon","tly","zxy","bakal","langyan"});

string *reward_four=({
"pound","xhx","wish","anything","zax","huanle","yuhe","tianyi","none","miclon",
"denis","xing","lazylong","sea","strong","zyf","xuedao","ddyy","aojian"});

void give_reward(object ob,int pot,int office_number,int point)
{
    ob->add("potential",pot);
    ob->add("office_number",office_number);
    ob->add("char_lev/points",point);
    
    tell_object(ob,"你得到了：\n"+
    chinese_number(pot)+"点潜能\n"+
    chinese_number(office_number)+"点功绩\n"+
    chinese_number(point)+"点属性！\n");
    
    tell_object(ob,"为了让你的潜能不至于浪费，还是先存到"+name()+"这里比较好！\n");
    
    log_file("REWARD_TEST_ID",ob->query("name")+" "+ob->query("id")+"得到测试奖励:"+
      "潜能:"+chinese_number(pot)+"点;功绩:"+chinese_number(office_number)+
      "点;属性点:"+chinese_number(point)+"点。获得时间："+ctime(time())+"\n");
    
}

int give_test_reward()
{
  object ob;
  string id;
  
  ob=this_player();
  id=ob->query("id");  
  
  if(!SCORE_D->RemoveOne(id)){
    command("say 施主心地不诚，以后如何行走江湖？\n");
    return 1;
  }
  
  
  if(member_array(id,reward_one)!=-1){
    tell_object(ob,"\n恭喜你，你得到的是“特殊贡献奖励”！\n");
    command("hehe "+id);
    
    give_reward(ob,4000,20,8);
    return 1;
  }
  if(member_array(id,reward_two)!=-1){
    tell_object(ob,"\n恭喜你，你得到的是“高级贡献奖励”！\n");
    command("hehe "+id);
    
    give_reward(ob,3000,15,6);
    return 1;
  }
  if(member_array(id,reward_three)!=-1){
    tell_object(ob,"\n恭喜你，你得到的是“有贡献奖励”！\n");
    command("hehe "+id);
    
    give_reward(ob,2000,10,4);
    return 1;
  }
  if(member_array(id,reward_four)!=-1){
    tell_object(ob,"\n恭喜你，你得到的是“普通测试奖励”！\n");
    command("hehe "+id);
    
    give_reward(ob,1000,5,2);
    return 1;
  }
  tell_object(ob,"\n恭喜你，你得到的是“测试登录奖励”！\n");
    command("hehe "+id);
    
    give_reward(ob,500,5,1);
    return 1;
  
  
  return 1;
  
}
  
  
  
