#include <ansi.h>

string give_gift(); 
private mixed *story = ({          
        "成都某寺院的一角....",
        "小骗子：“都JIEYIN几百次了，怎么还没事发生？”",
        "忽然间，一个老和尚走了过来......",
        "小骗子狂喜！",
        "小骗子向真言大师打听有关『九字真言』的消息。",
        "真言大师说：“你想要啊？小骗子，你要是想要的话你就说话嘛，你不说我怎么知道你想要呢， ”",
        "真言大师说：“虽然你很有诚意地看着我，可是你还是要跟我说你想要的。你真的想要吗？那你就拿去吧！”",
        "真言大师说：“你不是真的想要吧？难道你真的想要吗？ ”",
        "小骗子：“算了，还是不要了，但你告诉我为什么要JIEYIN那么多次你才出来吗？”",
        "真言大师向小骗子说：“哦，是这样的，由于你的本名叫一千，所以一定要JIEYIN一千次我才出来见你。”",
        "真言大师：“不过嘛，我看你搞了那么久，就出来看看你到底急成什么个猴样了。”",
        "真言大师对小骗子大笑起来，笑的气都快喘不过来了.",
        "小骗子：“.......”",
        "真言大师:“......”",
        "阿雅走了过来。",
        "真言大师：“.........”",
        "真言大师：“！！！！！！！”",
        "小骗子和阿雅把真言大师按在地上,拼命地往死里打！",
        "只听见“啪”的一声从真言大师嘴里甩出了一副假牙。",
        (: give_gift :)
});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

string give_gift()
{
        STORY_D->give_gift("/clone/quest/jiaya.c", 1,
                           HIM "\n“啪”的一声一副假牙掉到你面前。\n\n" NOR);
        return HIM "真言大师被小骗子杀死了。\n" NOR;
}
