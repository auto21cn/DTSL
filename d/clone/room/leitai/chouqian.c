
inherit ROOM;

void create()	
{
	set("short", "抽签大厅");
	set("long", @LONG
这里是天下帮会比武大会的抽签大厅。大厅的正中间放着一
张大桌子，上面放着一个抽签的盒子。大厅两旁火把林立，显出
庄严肃穆的气氛。
LONG);
    
 	set("exits",([
 	  "down":__DIR__"kantai1",
 	  ]));
 	set("no_death",1);
        set("leitai",1);
 	set("no_sleep",1);
 	set("no_channel","还是好好抽签吧！\n");
 	set("no_get",1);
 	set("no_quit",1);
 	set("no_fight",1);
	
      setup();
    
}
