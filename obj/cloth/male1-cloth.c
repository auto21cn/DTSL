// male1-cloth.c
//
// This is the basic equip for players just login.

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("����", ({ "cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
		set("long", "һ������ͨ�Ĳ��¡�\n");
                set("material", "cloth");
		set("value", 0);
                set("armor_prop/armor", 1);
              set("no_give", "�����Ķ������ܸ��ˡ�\n");

        }
        setup();
}
