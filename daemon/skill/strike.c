// strike.

inherit SKILL;

mapping *action=({
([ "action":"$N身行站住,右掌向前一推,一招[推门望月]拍向$n！",
    "dodge":20,
    "damage":10,
    "force":10,
    "damage_type":"於伤",
]),
([  "action":"$N身行向后一退,双掌推出,正是一招[排山倒海]向$n猛的拍去!",
    "dodge":10,
    "damage":15,
	"damage_type":"於伤",
]),
([
 "action":"$N突然转身,一招[回头望月]向$n拍了过去",
 "dodge":10,
 "damage":10,
 "damage_type":"於伤",
])



});   







mapping query_action(object me,object weapon)
{
	return action[random(sizeof(action))];
}

string query_type()
{
	return "base";
}


string perform_action_file(string action)
{
	return __DIR__"hand/"+action;
}