// Room: /d/hengshan/xuankong2.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "��������¥");
	set("long", @LONG
�����������µ�����¥��Ҳ���ϱ�ͤ���������ڶ�������ʯѨ����
��Ϊ����¥���ջ��������ȫ���涫�������ϱ�Σ¥���������·ֶϣ�
���Ǽ��ա�
LONG
	);
	set("exits", ([
		"north"   : __DIR__"zhanqiao",
		"southup" : __DIR__"zhandao",
	]));
	setup();
        replace_program(ROOM);
}
