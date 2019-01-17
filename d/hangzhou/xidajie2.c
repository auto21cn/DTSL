
inherit ROOM;


void create ()
{
  set ("short","西大街");
  set ("long", @LONG
这里是杭州的西大街。西边就是杭州的旅游胜地西湖的东岸了。北
边是一个凉亭，有很多游人在里边谈笑风声，欣赏着西湖美丽的景色。
南边有一家兵器店，里面传来了乒乓敲打兵器的声音。这里的行人很多，
热闹非凡。
LONG);

  set("exits", ([ 
 "north":__DIR__"liangting",
  "west":__DIR__"dongan1",
  "east":__DIR__"xidajie1",
  "south":__DIR__"bingqidian",
         ]));
  set("objects",([
    "/d/clone/npc/lingzhigao":1,
    ]));
set("outdoors","hangzhou");
  
  set("valid_startroom", 1);
  setup();
 
}

