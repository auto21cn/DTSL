
inherit ROOM;
void create()	
{
	set("short","村南小路");
	set("long", @LONG
这里是扬州玩家村的村南小路。由于目前这里的人口非常少，
所以这里也只是修建了一条小路。东边有一户人家，据说这
户人家的男主人是一风（LIY），女主人是天外神龙（FOXGOD）。
两人都是武林中数一数二的高手。因为两人刚刚结婚不久，所
以搬到这里来住了。
LONG);
    set("exits", ([
	        "south" : __DIR__"door",
	        "east":__DIR__"liy_foxgod",
	        "west":__DIR__"tong_and_wife",
	        "north":__DIR__"nandajie2",
 	]));
 	
      setup();
      replace_program(ROOM);
	
}
