// Room: /d/longyan/hotel.c

inherit ROOM;

void create()
{
	set("short", "�м��ջ");
	set("long", @LONG
�������Զ�������ġ��м��ջ������˵���۴岻���
�����䷱���̶�Ҳ������ĳЩ���ǡ������ջ��˵�ɣ�ֻ����
����ֻ�������߸ߵ��������ſڣ�ÿ��ҹ���ͻ������յ�
��������һ���ֵƻ�ͨ�����ٿ���ջ�ڲ����������Σ��մɾ�
�������Կ�ջ���ɡ�������С������ë������ͣ��������æ��
æȥ�������ֺ���
LONG
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"mktstr2",
]));

	setup();
	replace_program(ROOM);
}