inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һ��Сɽ·����������ȥ�����Կ���һ��������������ľï
ʢ�����Զ��Ǹ߸ߵ���ľ�������������ĺ����ˡ�
LONG );

	set("exits", ([
                          "east"      : __DIR__"shanlu2",
"northup":"/d/clone/room/lingwu/chanyuan/shanlu",
                         "west"      : "/d/chanyuan/houmen",
		
	]));
	set("outdoors", "xingyang");
	setup();
	replace_program(ROOM);
}


