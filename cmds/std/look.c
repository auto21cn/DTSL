// look.c
//modify by yanyan.2001.  

#include <room.h>
#include <ansi.h>
#include <combat.h>
#define TIME_TICK1 ((time())*60)
#define MAX_LIGHT_TIME 1200

inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string unique_long(object obj);
string unique_armor_long(object obj);

string power_level(int power);
string query_equip(object obj);

string *power_level_desc = ({
	BLU "不堪一击" NOR,	BLU "不足挂齿" NOR,	BLU "初学乍练" NOR,
	BLU "略窥门径" NOR,	BLU "粗通皮毛" NOR,	BLU "平平常常" NOR,
	HIB "普普通通" NOR,	HIB "马马虎虎" NOR,	HIB "略有小成" NOR,
	HIB "举重若轻" NOR,	HIB "驾轻就熟" NOR,	HIB "已有小成" NOR,
	CYN "心领神会" NOR,	CYN "了然於胸" NOR,	CYN "略有大成" NOR,
	CYN "出神入化" NOR,	CYN "豁然贯通" NOR,	CYN "已有大成" NOR,
	HIC "举轻若重" NOR,	HIC "所向披靡" NOR,	HIC "炉火纯青" NOR,
	HIC "所向无敌" NOR,	HIC "登峰造极" NOR,	HIC "一代宗师" NOR,
	HIR "震今铄古" NOR,	HIR "深不可测" NOR,	HIR "天人合一" NOR,
});

string *clr_msg=({"RED","GRN","YEL","BLU","MAG","CYN","WHT",
		"HIR","HIG","HIY","HIB","HIM","HIC","HIW","BLK"		
});
string *clr=({RED,GRN,YEL,BLU,MAG,CYN,WHT,
		HIR,HIG,HIY,HIB,HIM,HIC,HIW,BLK		
});
string *per_msg_male1 = ({
	CYN "长得伟岸英挺，顾盼之间，神采飞扬。\n" NOR,
	CYN "丰姿英伟，气宇轩昂，确实是人中龙凤。\n" NOR,
});
string *per_msg_male2 = ({
	CYN "英俊潇洒，风度翩翩。\n" NOR,
	CYN "相貌出众，面目俊朗。\n" NOR,
	CYN "面貌清奇，丰姿非俗。\n" NOR,
});
string *per_msg_male3 = ({
	CYN "相貌平平，没什么好看的。\n" NOR,
	CYN "五官端正。\n" NOR,
});
string *per_msg_male4 = ({
	CYN "相貌凶恶，满脸横肉。\n" NOR,
	CYN "暴睛环眼，嘴脸凶顽。\n" NOR,
});
string *per_msg_male5 = ({
	CYN "长得一副姥姥不疼，舅舅不爱的模样。\n" NOR,
	CYN "长得蔫蔫的，一副无精打采的模样。 \n" NOR, 
	CYN "五短三粗，肥头大耳，大概是猪八戒的本家。 \n" NOR, 
});
string *per_msg_female1 = ({
	CYN "长发如云，肌肤胜雪，不知倾倒了多少英雄豪杰。 \n" NOR,
	CYN "俏脸生春，妙目含情，轻轻一笑，不觉让人怦然心动。 \n" NOR,
	CYN "风情万种，楚楚动人，当真是我见犹怜。 \n" NOR, 
	CYN "美奂绝伦，堪称人间仙子！\n" NOR,
});
string *per_msg_female2 = ({
	CYN "婷婷玉立，容色秀丽，风姿动人。 \n" NOR,
	CYN "玉面娇容花含露，纤足细腰柳带烟。 \n" NOR,
	CYN "面带晕红，眼含秋波。举手投足之间，确有一番风韵。 \n" NOR,
	CYN "有沉鱼落雁之容,避月羞花之貌！\n" NOR,
});
string *per_msg_female3 = ({
	CYN "虽算不上绝世佳人，也颇有几份姿色。 \n" NOR,
	CYN "长得还不错，颇有几份姿色。\n" NOR,
});
string *per_msg_female4 = ({
	CYN "相貌平平,还看得过去。\n" NOR,
});
string *per_msg_female5 = ({
	CYN "长得比较难看。 \n" NOR,
	CYN "长得………唉！\n" NOR,
});
string *per_msg_kid1 = ({
	CYN "月眉星眼，灵气十足。\n" NOR,
	CYN "机灵活泼，神态非凡。\n" NOR,
	CYN "面若秋月，色如晓花。\n" NOR,
});
string *per_msg_kid2 = ({
	CYN "隆额大眼，脸色红润。\n" NOR,
	CYN "胖胖嘟嘟，逗人喜欢。\n" NOR,
	CYN "细皮嫩肉，口齿伶俐。\n" NOR,
});
string *per_msg_kid3 = ({
	CYN "肥肥胖胖，小鼻小眼。\n" NOR,
	CYN "呆头呆脑，笨手笨脚。\n" NOR,
});
string *per_msg_kid4 = ({
	CYN "身材矬矮，傻里傻气。\n" NOR,
	CYN "五官不整，四肢不洁。\n" NOR,
});
string *per_msg_kid5 = ({
	CYN "蓬头垢脚，脸黄肌瘦。\n" NOR,
	CYN "神如木鸡，面有病色。\n" NOR,
});

string ride_suffix(object me)
{
	string ridemsg=0;
	object ridee;
	if (ridee = me->ride()) { 
		if (environment(ridee) != environment(me) ||
		!living(ridee) || !living(me)) {
			me->delete_temp("ridee");
			ridee->delete_temp("rider");
			ridee=0;
		}else ridemsg = ridee->query("ride/msg")+"在"+ridee->name()+"上";
	}
	if (! ridee) {
	me->add_temp("apply/dodge",-me->query_temp("ride/dodge"));
	me->set_temp("ride/dodge",0);
	}
	return ridemsg;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;
	string str;

	if(environment(me)&&stringp(str=environment(me)->query("no_look_msg"))
	   &&!wizardp(me) ) return notify_fail(str);

	if(!arg) result = look_room(me, environment(me));
	else if((obj = present(arg, me)) || (obj = present(arg, environment(me))) ){
			if(obj->is_character() && !obj->query("carrier") ) 
				result = look_living(me, obj);
			else result = look_item(me, obj);
		}
		else if(wizardp(me)&& (obj = find_player(arg)) ) 
			result = look_living(me, obj);
		else result = look_room_item(me, arg);
	return result;
}
int look_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str,str1="",str2,*dirs,long,color,ridemsg = "";
	object room;

	if(!env){
		write(HIY"你的四周灰蒙蒙地一片，什么也看不见。\n"NOR);
		me->move(VOID_OB);
		return 1;
	}

	if (NATURE_D->is_look_night(me,env)) 
			long=HIB"四周光线很暗，黑漆漆的一片，什么也看不清楚。你抬头望望天
空，但见无垠的夜空中繁星闪烁，银河好似一条玉带般划过天际一轮
皎洁的明月高挂在天空之中。\n"NOR;
		else long=env->query("long");

	color=NATURE_D->outdoor_room_outcolor();
	for(i=0; i<sizeof(clr_msg); i++)
		if(color==clr_msg[i]){color=clr[i];i=20;}
	if(i!=21) color="";

	str=sprintf( "%s - %s\n　　%s"+color+"%s"+NOR,
		env->query("short"),wizardp(me)? file_name(env):"",long,
		env->query("outdoors")? NATURE_D->outdoor_room_description():"");

	if(mapp(exits = env->query("exits"))) 
	{
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if((int)env->query_door(dirs[i],"status") & DOOR_CLOSED) dirs[i] = 0;
		dirs -= ({ 0 });
		if(sizeof(dirs)==0) 
			str+="　　这里没有任何明显的出路。\n";
		else 
		if( sizeof(dirs)==1 ){ 
			//str+="　　这里唯一的出口是 "HIY+dirs[0]+HIW"。\n"NOR;
			room = load_object(exits[dirs[0]]);
			if(objectp(room)&&room->valid_leave(me,dirs[0]))
			str+="　　这里唯一的出口是 "HIY+dirs[0]+NOR+"("+HIG+room->query("short")+NOR+")。\n"NOR;
		}
		else {
			//changed by Yanyan 2004.9.24
			/*str += sprintf("　　这里明显的出口有 "HIY"%s"HIW" 和 "HIY"%s"HIW"。\n"NOR,
				implode(dirs[0..sizeof(dirs)-2], HIW"、"HIY), dirs[sizeof(dirs)-1]);*/
			str += "　　这里明显的出口有";
			for(i=0;i<sizeof(dirs);i++){
				room = load_object(exits[dirs[i]]);				
                if(objectp(room)){
					str += HIY+dirs[i]+NOR+"("+HIG+room->query("short")+NOR+")";
					if(i>0&&i<sizeof(dirs)-1&&(i+1)%2==0)
						str += "\n"+"　　                ";
					else
					if(i<sizeof(dirs)-1)
						str += "、";
                }
			}
			str += "\n";
		}
		
	}

	inv = all_inventory(env);
	i=sizeof(inv);
	if(NATURE_D->is_look_night(me,env)){
			while(i--){
			if( !me->visible(inv[i]) ) continue;
			if( inv[i]==me ) continue;
			if( inv[i]->query("no_shown")&& (!wizardp(me) || !me->query("env/shown"))) continue;
			
			if (ridemsg = ride_suffix(inv[i]))
				str1 = "  一个朦胧的身影，看不清楚是谁 <"+ridemsg+">\n"+str1;
			else if(inv[i]->is_character() && (inv[i]->query("race")=="人类"
				|| inv[i]->query("race")=="妖魔") )
				str1= "  一个朦胧的身影，看不清楚是谁。\n"+str1;
			else if( inv[i]->is_character() && inv[i]->query("race")=="野兽" )
				str1 = "  "+inv[i]->short()+"\n"+str1;
			else str1="  一团模模糊糊的东西。\n"+str1;
		}
        }
	else while(i--){
		if( !me->visible(inv[i]) ) continue;
		if( inv[i]==me ) continue;
		if( inv[i]->query("no_shown")&& (!wizardp(me) || !me->query("env/shown"))) continue;
		if(ridemsg=ride_suffix(inv[i])) str2="　"+inv[i]->short()+" <"+ridemsg+">";
		else{ 
		if(inv[i]->query("teams")) str2=" "+"一群"+inv[i]->short(); //add by yanyan.
		else str2="　" + inv[i]->short();
		}
		if(wizardp(me)) str1=str2+"  "+base_name(inv[i])+"\n"+str1;
		else str1=str2+"\n"+str1;
	}
        write(str+str1);
        return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;
	string position,look_msg,carrier;

	if(obj->query("no_show_cont")) return 1;
	
	if(obj->query("skill_type")||obj->query("armor_prop"))
	 me->start_more(unique_long(obj));
	else
	me->start_more(obj->long());
	
	inv = all_inventory(obj);
	if(sizeof(inv)){
		inv = map_array(inv, "inventory_look", this_object());
		carrier=obj->query("carrier");
		if(!carrier || carrier==""){
			carrier="它";
			message("vision", sprintf(carrier+"里面装着：\n%s\n",
				implode(inv, "\n") ), me);
		}
		else if(look_msg=obj->query("look_msg")){
		message("vision", sprintf("%s\n%s\n", look_msg,
			implode(inv, "\n") ), me);
		}else{
		position=obj->query("position");
		if(!position || position=="") position="里";
		message("vision", sprintf("%s面有：\n%s\n", position,
			implode(inv, "\n") ), me);
		}
	}
        return 1;
}
string per_status_msg(int age, int per, string gender)
{
	if (age < 14) {
		if ( per>=25 )
			return ( per_msg_kid1[random(sizeof(per_msg_kid1))]);
		else if ( per>=20 )
			return ( per_msg_kid2[random(sizeof(per_msg_kid2))]);
		else if ( per>=15 )
			return ( per_msg_kid3[random(sizeof(per_msg_kid3))]);
		else if ( per>=10 )
			return ( per_msg_kid4[random(sizeof(per_msg_kid4))]);
		else return ( per_msg_kid5[random(sizeof(per_msg_kid5))]);
		}
		
	if ( gender == "男性" ) {
		if ( per>=25 )
			return ( per_msg_male1[random(sizeof(per_msg_male1))]);
		else if ( per>=20 )
			return ( per_msg_male2[random(sizeof(per_msg_male2))]);
		else if ( per>=15 )
			return ( per_msg_male3[random(sizeof(per_msg_male3))]);
		else if ( per>=10 )
			return ( per_msg_male4[random(sizeof(per_msg_male4))]);
		else return ( per_msg_male5[random(sizeof(per_msg_male5))]);
		}
		
	if ( gender == "女性" ) {
		if ( per>=25 )
			return ( per_msg_female1[random(sizeof(per_msg_female1))]);
		else if ( per>=20 )
			return ( per_msg_female2[random(sizeof(per_msg_female2))]);
		else if ( per>=15 )
			return ( per_msg_female3[random(sizeof(per_msg_female3))]);
		else if ( per>=10 )
			return ( per_msg_female4[random(sizeof(per_msg_female4))]);
		else return ( per_msg_female5[random(sizeof(per_msg_female5))]);
		}
	else return "";
}
string query_power(object me)
{
	mapping action;
	string skill_name;
	int attack_points;
	
	if(!me->query("actionp")){
  	skill_name=me->reset_action(me->query_temp("weapon"));
    action=me->query("actions");
  }
  else{
  	action=me->query("actionp");
    skill_name=action["skill_name"];
  }


	attack_points = COMBAT_D->get_damage(me,0,me->query_temp("weapon"),action,0,skill_name);

	return  power_level(attack_points*15);
}
string power_level(int power)
{

	int lvl;
	int rawlvl;
	if(power<0) power=0;
	rawlvl = (int) pow( (float) 1.0 * power, 0.3);
	lvl = to_int(rawlvl);
                        if( lvl >= sizeof(power_level_desc) )
                                lvl = sizeof(power_level_desc)-1;
                        return power_level_desc[((int)lvl)];
}

string apply_msg(int p)
{
  if(p==0)
   return "毫无杀意";
  else
  if(p<3)
   return CYN"略带杀意"NOR;
  else
  if(p<7)
   return HIR"杀意微重"NOR;
  else
  if(p<10)
   return HIR"杀意甚浓"NOR;
  else return RED"杀意浓厚"NOR;
}
  

int look_living(object me, object obj)
{
	string str,limb_status,ridemsg,pro,ogender,orace;
	mixed *inv;
	mapping my_fam,fam,ofamily;
	int oage;
 
	ofamily=obj->query("family");
	ogender=obj->query("gender");
	orace=obj->query("race");
	oage=obj->query("age");

	if(obj->query("fake_age") ) oage=obj->query("fake_age");

	if( me!=obj )
	      if(me->query("id")==obj->query("couple/couple_id"))
	        if(me->query("gender")=="男性")
	        message("vision", "你的丈夫"+me->name() + "正温柔地看着你。\n", obj);
	        else message("vision", "你的妻子"+me->name() + "正温柔地看着你。\n", obj);
	     else if(me->query("id")==obj->query("home/mother_id"))
	        message("vision","你的母亲"+me->name()+"正慈祥地望着你。\n",obj);
	      else if(me->query("id")==obj->query("home/father_id"))
	        message("vision","你的父亲"+me->name()+"正慈祥地望着你。\n",obj);
	     else if(me->query("home/father_id")==obj->query("id")||
	            me->query("home/monther_id")==obj->query("id"))
	          message("vision","你的孩子"+me->name()+"正望着你。\n",obj);
	        else message("vision", me->name() + "正盯着你看，不知道打些什么主意。\n", obj);
        
	str = obj->long();
    if(obj->query("teams")) {write(str);return 1;} //add by yanyan.
	str = replace_string(str, "$n", me->name());
	str = replace_string(str, "$N", obj->name());
str = replace_string(str, "$C", RANK_D->query_respect(obj));
	str = replace_string(str, "$c", RANK_D->query_rude(obj));
	str = replace_string(str, "$R", RANK_D->query_respect(me));
	str = replace_string(str, "$r", RANK_D->query_rude(me));


	pro = (obj==me) ? gender_self(ogender) : gender_pronoun(ogender);

	ridemsg = ride_suffix(obj);
	if (ridemsg) str+=pro+"正"+ridemsg+"。\n";

	if( orace=="人类" && intp(oage) )
		if(oage<10) str+=sprintf("%s看起来显然还不到十岁。\n", pro);
		else str+=sprintf("%s看起来约%s多岁。\n", pro, chinese_number(oage/10*10));

	if(obj->query("id")==me->query("couple/couple_id") ) {
		if( (string)me->query("gender")=="女性" ){
		str += sprintf("%s是你的丈夫。\n", pro);
		}
		else{
	str += sprintf("%s是你的妻子。\n", pro);
		}
	}
	if(obj->query("home/mother_id")==me->query("id")||
	   obj->query("home/father_id")==me->query("id")){
	   if(obj->query("gender")=="女性")
	     str+=sprintf("%s是你的女儿.\n",pro);
	   else str+=sprintf("%s是你的儿子.\n",pro);}
	if(me->query("home/mother_id")==obj->query("id")||
	   me->query("home/father_id")==obj->query("id")){
	   if(obj->query("gender")=="女性")
	     str+=sprintf("%s是你的母亲.\n",pro);
	   else str+=sprintf("%s是你的父亲.\n",pro);}
	if(me->query("id")==obj->query("couple/couple_id"))
          if(obj->query("gender")=="女性")
           if(obj->query("makelove_times")&&obj->query("makelove_times")<4) str+=sprintf("她已经有身孕了。\n");
           else if(obj->query("makelove_times")&&obj->query("makelove_times")<40) str+=sprintf("她已经怀孕"+chinese_number(obj->query("makelove_times")/4)+
                      "个多月了。\n");     
	if( obj!=me && mapp(fam = ofamily) && mapp(my_fam = me->query("family")) 
	&& fam["family_name"] == my_fam["family_name"] ) {
		if( fam["generation"]==my_fam["generation"] ) {
			if( ogender == "男性" ) str += sprintf( pro + "是你的%s%s。\n",
				my_fam["master_id"] == fam["master_id"] ? "": "同门",
				my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else str += sprintf( pro + "是你的%s%s。\n",
				my_fam["master_id"] == fam["master_id"] ? "": "同门",
				my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		}else
		if( fam["generation"] < my_fam["generation"] ) {
			if(member_array(my_fam["master_id"],obj->parse_command_id_list())>-1)
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else str += pro + "是你的师叔。\n";
		}else{
		if( fam["generation"] - my_fam["generation"] > 1 )
			str += pro + "是你的同门晚辈。\n";
		else if( fam["master_id"] == me->query("id") )
			str += pro + "是你的弟子。\n";
		else str += pro + "是你的师侄。\n";
		
		}
	}

	if( obj->query("max_kee") )
		str+=pro+COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";

	if( obj->query("looking") ){
		str += pro + (string)obj->query("looking") + "\n";
	} else {
		string looking= per_status_msg((int)obj->query("age"),(int)obj->query_per(), ogender);
		if( orace!="人类" || base_name(obj)==CORPSE_OB ) looking="";
		if( strlen(looking)>1) str += pro + looking;
	}
	if(me->query("combat_exp")+200000>obj->query("combat_exp")||me==obj)
	{str+=pro+sprintf("武功看起来好象");
	str+=query_power(obj)+"。\n";}
	else  if(obj->query("race")=="人类")
	      if(obj->query("gender")=="男性")str+="他的武功看不出深浅。\n";
	      else str+="她的武功看不出深浅。\n";
        if(me->query("shili")&&obj->query("shili")&&
        me->query("shili/name")==obj->query("shili/name")&&me!=obj)
		     str +=pro +"是和你同一势力的人。\n";
	if(userp(obj) && ((int)(obj->query("food")*10/obj->max_food_capacity())<3
		||(int)(obj->query("water")*10/obj->max_water_capacity())<3) )
		str+=pro+"看起来"MAG"饥渴难忍"NOR"。\n";
	if(userp(obj) && (int)obj->query_encumbrance()* 10/(int)obj->query_max_encumbrance()>6)
		str+=pro+"看起来"MAG"行动吃力"NOR"。\n";
	if(obj->query("bellicosity")>40000) str+=pro+"看起来"MAG"杀气重重"NOR"。\n";
        
       // str +=pro+"看起来"+apply_msg(obj->query("apply_points"))+"。\n";
        if(obj->query_temp("bsy_skill_damage")
        &&time()-obj->query_temp("bsy_damage_time")<obj->query_temp("bsy_skill_damage")/7)
        str +=pro+"看起来已经受了不死印的内伤。\n";
        
        if(obj->query_temp("csj_skill_damage")
        &&time()-obj->query_temp("csj_damage_time")<obj->query_temp("csj_skill_damage")/7)
        str +=pro+"看起来已经受了长生诀的内伤。\n";
        
	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
	str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带着：\n%s\n",
	pro, implode(inv, "\n") );
	}
	
	me->start_more(str);

	if( obj!=me && living(obj)
		&&!environment(obj)->query("no_fight")
		&&!environment(obj)->query("sleep_room")
		&& obj->query("bellicosity")-1000 > (int)me->query("bellicosity")
	   &&me->query("id")!=obj->query("couple/couple_id")&&
	   me->query("home/mother_id")!=obj->query("id")&&me->query("home/father_id")!=obj->query("id")
	   &&obj->query("home/mother_id")!=me->query("id")&&obj->query("home/father_id")!=me->query("id")
	   &&!obj->is_busy()){
		write( obj->name() + "突然转过头来瞪你一眼。\n");
		COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

string inventory_look(object obj, int flag)
{
	string str=obj->short();
	if( obj->query("equipped") ) str = HIM"◆"NOR+ query_equip(obj);
	else if( !flag ) str = "  " + str;
	else return 0;
	return str;
}

string query_equip(object obj)
{
        string str,units;

        units =obj->query("unit");
        str = obj->name();
        if (obj->query("armor_type"))
        switch( obj->query("armor_type") ) {
                case "cloth":
                case "armor":
                        str = "身穿一"+ units + str;
                        break;
                case "boots":
                        str = "脚上穿着一" + units + str;
                        break;
                case "head":
                case "neck":
                case "wrists":
                case "finger":
                case "hands":
                        str ="戴着一"+ units + str;
                        break;
                case "waist":
                        str = "腰间绑得有一"+units+str;
                        break;
                default:
                        str = "装备着"+str; 
                        }
        else
        if( obj->wield() )
                if (obj->query("skill_type")=="throwing")
                str ="身上带着"+str;
                else
                str ="手持一" + units + str;
        return str;     
}

int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !env = environment(me) ){
		write(HIY"你的四周灰蒙蒙地一片，什么也看不见。\n"NOR);
		me->move(VOID_OB);
		return 1;
	}
	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ){
		if( stringp(item[arg]) ) write(item[arg]);
		else if( functionp(item[arg]) ) write((string)(*item[arg])(me));
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = load_object(exits[arg])) ) look_room(me, env);
		else return notify_fail("那边好像没有什么。\n");
		return 1;
	}
	return notify_fail("你要看什么？\n");
}

string *wdamage=({
BLU"寻常威力"NOR,BLU"微具威力"NOR,HIB"轻微威力"NOR,HIB"颇具威力"NOR,CYN"较大威力"NOR,
CYN"巨大威力"NOR,GRN"非同凡响"NOR,GRN"无与伦比"NOR,HIC"无可匹敌"NOR,HIC"所向披靡"NOR,
HIY"世间罕见"NOR,HIY"举世无双"NOR,HIG"惊世骇俗"NOR,HIG"空前绝后"NOR,HIW"震惊寰宇"NOR,
HIW"神乎其神"NOR,HIR"劈山断海"NOR,HIR"惊天动地"NOR,RED"毁天灭地"NOR,RED"无穷无尽"NOR,
});

string *wstrong=({
BLU"轻微"NOR,BLU"少量"NOR,HIB"不错"NOR,CYN"较大"NOR,GRN"很大"NOR,HIC"非同凡响"NOR,
HIY"无与伦比"NOR,HIG"无可匹敌"NOR,HIW"世间罕见"NOR,HIR"举世无双"NOR,
});

string *strongs=({BLU"不堪一击"NOR,BLU"还算结实"NOR,HIB"比较结实"NOR,GRN"非常结实"NOR,
GRN"坚固异常"NOR,HIG"坚不可摧"NOR,HIR"无可匹敌"NOR,});

string *supers=({
"稍微有些锋利","微具一些锋利","有些锋利","比较锋利","非常锋利",
"异常锋利","具有吹毛断发般的锋利","具有削铁如泥般的锋利",
"劈山斩石般的锋利",
});

string *levs=({
BLU"极少"NOR,HIB"很少"NOR,CYN"少量"NOR,GRN"些许"NOR,HIC"不多"NOR,
HIY"较多"NOR,HIG"很多"NOR,HIW"大量"NOR,HIR"极多"NOR,RED"罕见"NOR,
});

string unique_long(object obj)
{
   string longs;
   
   int min_damage,max_damage;
   int super=0;
   int dodge=0,parry=0,armor=0,enhance_min_damage=0,enhance_max_damage=0,double_damage=0;
   int intl=0,con=0,dex=0,str=0,kar=0,per=0;
   int flag=0;
   int wield_str,wield_con,wield_dex,wield_int;
   int wield_force,wield_maxforce;
   int line1_flag=0,line2_flag=0,line3_flag=0,line4_flag=0,line5_flag=0,need_flag=0;
   
   int no_need_force=0,no_need_maxforce=0,no_need_sx=0;
   int reduce_force=0,reduce_maxforce=0,reduce_sx=0;
   
   int weapon_or_armor;
   string obj_type,equip_type;
   
   if(obj->query("weapon_prop")){
    obj_type="weapon_prop";
    equip_type="wield";
    weapon_or_armor=1;
   }
   else{
    obj_type="armor_prop";
    equip_type="wear";
    weapon_or_armor=0;
   }
    
   min_damage=obj->query(obj_type+"/min_damage")+obj->query("user_skill")/10;
   max_damage=obj->query(obj_type+"/damage")+obj->query("user_skill")/10;
   super=obj->query("super");
   
   dodge=obj->query(obj_type+"/dodge");
   if(dodge<0) dodge=0;
   
   if(weapon_or_armor)
    parry=obj->query("weapon_prop/armor");
   else{
    armor=obj->query("armor_prop/armor");
    if(armor<0) armor=0;
    parry=obj->query("armor_prop/parry");
   }
   
   enhance_min_damage=obj->query(obj_type+"/enhance_min_damage");
   enhance_max_damage=obj->query(obj_type+"/enhance_max_damage");
   double_damage=obj->query(obj_type+"/double_damage");
   intl=obj->query(obj_type+"/intelligence");
   con=obj->query(obj_type+"/constitution");
   dex=obj->query(obj_type+"/dodgeaction");
   str=obj->query(obj_type+"/strength");
   kar=obj->query(obj_type+"/karma");
   per=obj->query(obj_type+"/personality");
   
   wield_str=obj->query(equip_type+"_str");
   wield_dex=obj->query(equip_type+"_dex");
   wield_con=obj->query(equip_type+"_con");
   wield_int=obj->query(equip_type+"_int");
   wield_force=obj->query(equip_type+"_force");
   wield_maxforce=obj->query(equip_type+"_maxforce");
   
   no_need_force=obj->query("no_need_force");
   no_need_maxforce=obj->query("no_need_maxforce");
   no_need_sx=obj->query("no_need_sx");
   
   reduce_force=obj->query("reduce_force");
   reduce_maxforce=obj->query("reduce_maxforce");
   reduce_sx=obj->query("reduce_sx");
   
   if(!obj->query("long"))
    obj->set("long",obj->short()+"\n");
   longs=obj->query("long");
   
   if(weapon_or_armor)
   longs+="它至少具有【"+wdamage[min_damage/25>sizeof(wdamage)-1?sizeof(wdamage)-1:min_damage/25]+"】的威力，并可达到"+
              "【"+wdamage[max_damage/25>sizeof(wdamage)-1?sizeof(wdamage)-1:max_damage/25]+"】的威力。\n";
   else
   longs+="它具有【"+wstrong[armor/25>sizeof(wstrong)-1?sizeof(wstrong)-1:armor/25]+"】的防御。\n";
   
   if(dodge>0){
	  longs+="它的附加属性为：\n【"+levs[dodge/10>sizeof(levs)-1?sizeof(levs)-1:dodge/10]+"命中";
	  line1_flag=1;	  
	}
	if(parry>0){
	  if(!line1_flag){
	   longs+="它的附加属性为：\n【"+levs[parry/10>sizeof(levs)-1?sizeof(levs)-1:parry/10]+"防御";
	   line1_flag=1;	   
	  }
	  else{
	   longs+="、"+levs[parry/10>sizeof(levs)-1?sizeof(levs)-1:parry/10]+"防御";
	   
	  }
	}
	if(enhance_min_damage>0){
	  if(!line1_flag){
	   longs+="它的附加属性为：\n【"+levs[enhance_min_damage/5>sizeof(levs)-1?sizeof(levs)-1:enhance_min_damage/5]+"伤害";
	   line1_flag=1;	   
	  }
	  else{
	    longs+="、"+levs[enhance_min_damage/5>sizeof(levs)-1?sizeof(levs)-1:enhance_min_damage/5]+"伤害";
	   
	  }
	}	
	if(enhance_max_damage>0){
	  if(!line1_flag){
	   longs+="它的附加属性为：\n【"+levs[enhance_max_damage/5>sizeof(levs)-1?sizeof(levs)-1:enhance_max_damage/5]+"威力";
	   line1_flag=1;	   
	  }
	  else{
	    longs+="、"+levs[enhance_max_damage/5>sizeof(levs)-1?sizeof(levs)-1:enhance_max_damage/5]+"威力";
	   
	  }
	}	
	if(double_damage>0){
	  if(!line1_flag){
	   longs+="它的附加属性为：\n【"+levs[double_damage/5>sizeof(levs)-1?sizeof(levs)-1:double_damage/5]+"叠加威力";
	   line1_flag=1;	   
	  }
	  else{
	    longs+="、"+levs[double_damage/5>sizeof(levs)-1?sizeof(levs)-1:double_damage/5]+"叠加威力";
	   
	  }
	}
	if(intl>0){
	  if(!line2_flag){
	   if(!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[intl>sizeof(levs)-1?sizeof(levs)-1:intl]+"悟性";
	   else
	   longs+="】\n【"+levs[intl>sizeof(levs)-1?sizeof(levs)-1:intl]+"悟性";
	   line2_flag=1;
	  }
	  else{
	  
	    longs+="】\n【"+levs[intl>sizeof(levs)-1?sizeof(levs)-1:intl]+"悟性";
	  
	  }
	}
	if(con>0){
	  if(!line2_flag){
	   if(!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[con>sizeof(levs)-1?sizeof(levs)-1:con]+"根骨";
	   else
	   longs+="】\n【"+levs[con>sizeof(levs)-1?sizeof(levs)-1:con]+"根骨";
	   line2_flag=1;
	  }
	  else{
	   
	    longs+="、"+levs[con>sizeof(levs)-1?sizeof(levs)-1:con]+"根骨";
	   
	  }
	}
	if(dex>0){
	  if(!line2_flag){
	   if(!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[dex>sizeof(levs)-1?sizeof(levs)-1:dex]+"身法";
	   else
	   longs+="】\n【"+levs[dex>sizeof(levs)-1?sizeof(levs)-1:dex]+"身法";
	   line2_flag=1;
	  }
	  else{
	  
	    longs+="、"+levs[dex>sizeof(levs)-1?sizeof(levs)-1:dex]+"身法";
	  
	  }
	}
	if(str>0){
	  if(!line2_flag){
	   if(!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[str>sizeof(levs)-1?sizeof(levs)-1:str]+"臂力";
	   else
	   longs+="】\n【"+levs[str>sizeof(levs)-1?sizeof(levs)-1:str]+"臂力";
	   line2_flag=1;
	  }
	  else{
	   
	    longs+="、"+levs[str>sizeof(levs)-1?sizeof(levs)-1:str]+"臂力";
	   
	  }
	}	
	if(kar>0){
	  if(!line3_flag){
	   if(!line2_flag&&!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[kar>sizeof(levs)-1?sizeof(levs)-1:kar]+"运气";
	   else
	   longs+="】\n【"+levs[kar>sizeof(levs)-1?sizeof(levs)-1:kar]+"运气";
	   line3_flag=1;
	  }
	  else{
	   
	    longs+="】\n【"+levs[kar>sizeof(levs)-1?sizeof(levs)-1:kar]+"运气";
	   
	  }
	}
	if(per>0){
	  if(!line3_flag){
	   if(!line2_flag&&!line1_flag)
	   longs+="它的附加属性为：\n【"+levs[per>sizeof(levs)-1?sizeof(levs)-1:per]+"容貌";
	   else
	   longs+="】\n【"+levs[per>sizeof(levs)-1?sizeof(levs)-1:per]+"容貌";
	   line3_flag=1;
	  }
	  else{
	   
	    longs+="、"+levs[per>sizeof(levs)-1?sizeof(levs)-1:per]+"容貌";
	   
	  }
	}
   if(no_need_force>0){
   	 if(!line4_flag){
   	  if(!line3_flag&&!line2_flag&&!line1_flag)
   	   longs+="它的附加属性为：\n【无内力要求";
   	  else
   	   longs+="】\n【无内力要求";
   	  line4_flag=1;
   	 }
   	 else{
   	   longs+="、无内力要求";
   	 }
   }
  if(no_need_maxforce>0){
   	 if(!line4_flag){
   	  if(!line3_flag&&!line2_flag&&!line1_flag)
   	   longs+="它的附加属性为：\n【无最大内力要求";
   	  else
   	   longs+="】\n【无最大内力要求";
   	  line4_flag=1;
   	 }
   	 else{
   	   longs+="、无最大内力要求";
   	 }
   }
    if(no_need_sx>0){
   	 if(!line4_flag){
   	  if(!line3_flag&&!line2_flag&&!line1_flag)
   	   longs+="它的附加属性为：\n【无属性要求";
   	  else
   	   longs+="】\n【无属性要求";
   	  line4_flag=1;
   	 }
   	 else{
   	   longs+="、无属性要求";
   	 }
   }
    if(reduce_force>0){
     if(!line5_flag){
      if(!line4_flag&&!line3_flag&&!line2_flag&&!line1_flag)
       longs+="它的附加属性为：\n【降低内力要求"+chinese_number(reduce_force)+"点";
      else
       longs+="】\n【降低内力要求"+chinese_number(reduce_force)+"点";
      line5_flag=1;
     }
     else{
      longs+="、降低内力要求"+chinese_number(reduce_force)+"点";
     }
   }
   
   if(reduce_maxforce>0){
     if(!line5_flag){
      if(!line4_flag&&!line3_flag&&!line2_flag&&!line1_flag)
       longs+="它的附加属性为：\n【降低内力上限要求"+chinese_number(reduce_maxforce)+"点";
      else
       longs+="】\n【降低内力上限要求"+chinese_number(reduce_maxforce)+"点";
      line5_flag=1;
     }
     else{
      longs+="、降低内力上限要求"+chinese_number(reduce_maxforce)+"点";
     }
   }
   
   if(reduce_sx>0){
     if(!line5_flag){
      if(!line4_flag&&!line3_flag&&!line2_flag&&!line1_flag)
       longs+="它的附加属性为：\n【降低属性要求"+chinese_number(reduce_sx)+"点";
      else
       longs+="】\n【降低属性要求"+chinese_number(reduce_sx)+"点";
      line5_flag=1;
     }
     else{
      longs+="、降低属性要求"+chinese_number(reduce_sx)+"点";
     }
   }
   	   
	if(line1_flag||line2_flag||line3_flag||line4_flag||line5_flag)
	longs+="】\n";
	
	if(!no_need_sx&&wield_str-reduce_sx>0){
          longs+="装备需求：【"+chinese_number(wield_str-reduce_sx)+"】的臂力，";
	  need_flag=1;
	}
	else
	if(!no_need_sx&&wield_int-reduce_sx>0){
          longs+="装备需求：【"+chinese_number(wield_int-reduce_sx)+"】的悟性，";
	  need_flag=1;
	}
	else
	if(!no_need_sx&&wield_con-reduce_sx>0){
          longs+="装备需求：【"+chinese_number(wield_con-reduce_sx)+"】的根骨，";
	  need_flag=1;
	}
	else
	if(!no_need_sx&&wield_dex-reduce_sx>0){
          longs+="装备需求：【"+chinese_number(wield_dex-reduce_sx)+"】的身法，";
	  need_flag=1;
	}
	
	if(!no_need_force&&wield_force-reduce_force>0){
	 if(!need_flag)
           longs+="装备需求：【"+chinese_number(wield_force-reduce_force)+"】的内力。";
	 else
	   longs+="【"+chinese_number(wield_force-reduce_force)+"】的内力。";
	 need_flag=1;
	}
        if(!no_need_maxforce&&wield_maxforce-reduce_maxforce>0){
	  if(!need_flag)
            longs+="装备需求：【"+chinese_number(wield_maxforce-reduce_maxforce)+"】的内力上限。\n";
	  else
            longs+="【"+chinese_number(wield_maxforce-reduce_maxforce)+"】的内力上限。\n";
	}
	if(obj->query("poison_flag"))
	longs+="可以在上面涂抹些毒药。\n";
	
	if(weapon_or_armor){
	 if(!obj->query("max_strong"))
	  obj->set("max_strong",obj->query("strong"));
         longs+="它具有【"+strongs[obj->query("max_strong")/200>sizeof(strongs)-1?sizeof(strongs)-1:obj->query("max_strong")/200]+"】的坚固程度，";
         longs+="看起来"+"/feature/repair.c"->result_strong(obj->query("strong")*100/obj->query("max_strong"))+"";
	 if(super>0)
      longs+="，"+supers[super-1]+"。\n";
     else
      longs+="。\n";
	
    if(obj->query("user")!="") {
      if(obj->query("imbued"))
        longs+="它的主人是〖"+obj->query("saved")+"〗。\n";
      else
	longs+="它的主人是〖"+obj->query("user")+"〗。\n";
    } else
	longs+="它还没有主人。\n";
    }
    
	return longs;
	
}   


int help (object me)
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
	return 1;
}
