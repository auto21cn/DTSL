inherit ROOM;
void create()
{
	set("short", "����С·");
	set("long", @LONG
���Ƕ����ϵ�һ���Ӳݴ�������С·��������ƽʱûʲô�˼���
·�߿��Ų�֪����Ұ�������ߵ�������Ȼ�ߴ�ͦ�Ρ�����͸�����յ�
�������ǰ߲߰�����Ӱ�ӡ�
LONG );
	set("exits", ([
		"westdown": __DIR__"shanlu4",
		"northeast": __DIR__"shanlu2",
	]));
	/*set("objects", ([
		__DIR__"npc/yetu" : 1,
	]));*/
	set("outdoors", "liyang");
	setup();
	replace_program(ROOM);
}
