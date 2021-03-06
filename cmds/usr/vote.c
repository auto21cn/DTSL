// vote.c
// pickle 7-17-97
// dream 7/29/97

#include <ansi.h>
#include <login.h>
#define SYNTAX  "指令格式：vote < open | close > <频道> <人名> \n"
#define MAX_VOTER_PER_SITE 999

mapping votes_casted=([]), 
   voted_players=([]);
void nullify_vote(string myvariable, string choice, string username);
int determine_total();
int counting(mapping players, string my);
int max_voter, voter_site;
object *users;

void create() {
    // the following two are defined in /include/login.h
#ifdef MAX_VOTER_PER_SITE
    max_voter=MAX_VOTER_PER_SITE;
#else
    max_voter=2;
#endif
    
    voter_site=0;
#ifdef VOTER_SITE
    if(VOTER_SITE==1)
   voter_site=1;
#endif
}

string get_channle_name(string chan)
{
	switch(chan){
		case "chat": return "闲聊";
		case "rumor": return "谣言";
	}	
	
}

int main(object me, string arg)
{
    string chan, *channels, choice, choicename;
    string myid, playerid, myname, playername;
    string myvariable;
    object player;
    int nullify_vote_time=600, diff, i, chansize, chanmatch;
    int total_votes_required;
    mapping voted_player;
    string ip;
    int votes_count;
    string close_channel;

    if( !arg || sscanf(arg, "%s %s %s", choice, chan, playerid)!=3 ) return notify_fail(SYNTAX);

   if (me->query("age") < 16 ) return notify_fail("你年龄不满十六岁，没有投票权。\n");

    // sytax errors.
    if (choice != "open" && choice != "close") return notify_fail(SYNTAX);
    choicename = (choice == "open"? "打开":"关闭");
    // channels available: chat (made this option for future ease, if we open
    // more chat channels, such as channels for each menpai, ...)
    channels=({"chat","rumor"});
    chansize=sizeof(channels);
    while (chansize--)
    {
        if (chan == channels[chansize])
        {
            chanmatch = 1; break;
        }
        continue;
    }
    if (!chanmatch) return notify_fail("不能"+choicename+" "+chan+" 这个频道。请参照 help。\n");
    if (!player = find_player(playerid) ) 
   return notify_fail("目前找不到 "+playerid+" 这个人。\n");

    if (!me->visible(player) ) 
   return notify_fail("目前找不到 "+playerid+" 这个人。\n");

//    if (wizardp(player)) return notify_fail("Can't accuse wizard.\n");

    myvariable=choice+"_"+chan+"_"+playerid; // for checking double votes.
    myid=me->query("id");
    myname=me->query("name");
    playername=player->query("name");
    users=users();
	
	close_channel = "chblk_"+chan;
	
    if( choice=="close" ) {
   if (player->query(close_channel))
     return notify_fail(playername+"的交谈频道已经被关闭了。\n");
   }
    else {
   if (!player->query(close_channel))
     return notify_fail(playername+"的交谈频道已经被打开了。\n");
   }

    if (!undefinedp(voted_players[myvariable]))
   voted_player = (mapping)voted_players[myvariable];
    else
   voted_player = ([]);

    if (!undefinedp(voted_player[myid])) 
   return notify_fail("你已经投过相同的票了。\n");
    else {
   ip=query_ip_number(me);
   if(ip && voter_site==0)
       ip=ip[0..strsrch(ip, ".", -1)];
   voted_player += ([myid: (["obj":me, 
                       "ip":ip]) ]);
    }

    voted_players[myvariable] = voted_player;
    
    total_votes_required = determine_total();
    votes_count = counting(voted_player, myvariable);

        // remove vote in 5 min if not enough people respond
        if(undefinedp(votes_casted[myvariable]))
        {
            votes_casted+=([myvariable:1]);
       call_out("nullify_vote", nullify_vote_time, 
         myvariable, choicename, playername);
        }

        diff=total_votes_required-votes_count;

        // announce to mu
        if (diff>0)
       message("vote", HIW"【表决】"+myname+HIW+"投票"+choicename+playername+HIW+
         "的"+get_channle_name(chan)+"频道，需要" + chinese_number(total_votes_required)
         + "票通过，还差" + chinese_number(diff) +"票！\n"NOR, users);
        else
        {
       if (choice=="open") player->set(close_channel,0);
       else player->set(close_channel, 1);
       // block for 1 day.
       map_delete(voted_players, myvariable);
       map_delete(votes_casted, myvariable);
       message("vote", HIW"【表决】"+myname+HIW+"投票"+choicename+playername+HIW+
         "的"+get_channle_name(chan)+"频道，"+playername+HIW+"的交谈频道被"+choicename+"了！\n"NOR, users);
   }
    return 1;
}

int counting(mapping players, string myvariable) {
    int i=sizeof(players);
    int count=0;
    string *key;
    mapping site=([]);
    string ip;
    
    if(!i) return 0;
    key=keys(players);
    
    while(i--) {
   if(!players[key[i]]["obj"]) { // this player has logged out.
       map_delete(players, key[i]);
       continue;
   }
   
   if(!ip=players[key[i]]["ip"]) continue;
   
   if(undefinedp(site[ip])) {
       site[ip]=1;
   } else {
       site[ip]+=1;
   }

   // each site can count to max_voter.
   if(site[ip]<=max_voter) count++;
    }
    
    if(players)
      voted_players[myvariable] = players;
    else
      voted_players[myvariable] = ([]);

    return count;
}


int determine_total()
{
    int i, total_required;
    mapping site=([]);
    object *user=users();
    string ip;

    // to determine how many votes necessary to block channel

    i = sizeof(user);
    while (i--)
    {
        if (user[i]->query("age") > 16 ) {

       if(!ip=query_ip_number(user[i])) continue;

       if(ip && voter_site==0)
         ip=ip[0..strsrch(ip, ".", -1)];

       if(undefinedp(site[ip])) {
         site[ip]=1;
       } else {
         site[ip]+=1;
       }

       if(site[ip]<=max_voter) total_required++;
   }
    }

    total_required=total_required/3;
    if (total_required < 3) total_required=3;
    if (total_required > 20) total_required=20;
    return total_required;
}

void nullify_vote(string myvariable, string choice, string username)
{
    if (!undefinedp(voted_players[myvariable])) {
        message("vote", HIW"【表决】因为没有足够的人响应"+choice+username+HIW+
     "的交谈频道，投票取消了！\n"NOR, users);
        map_delete(voted_players, myvariable);
        map_delete(votes_casted, myvariable);
    }
}

int help()
{
    write(SYNTAX + @TEXT

投票关闭或打开一个人的交谈频道，只对十六岁以上的成人公民有效。
请勿滥用你的权利，故意捣乱的人会被抓入法庭。

关闭以及打开都需要不少于三票或者三分之一以上的票数。

目前频道仅包括 chat(包括dt频道) 和 rumor。

例：vote close chat yanyan

TEXT
    );
    return 1;
}
