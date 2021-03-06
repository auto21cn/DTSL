// help.c

#include "/doc/wizhelp.h"

inherit F_CLEAN_UP;

string *default_search = DEFAULT_SEARCH_PATHS;

#define WIZ_HELP_DIR "/doc/wizhelp/"

int main(object me, string arg)
{
	int i;
	string file, *search;

	// If no topic specified, give the topics.
	if( !arg ) {
		cat(WIZ_HELP_DIR + "topics");
		return 1;
	}

	// Else, try if a command name is specified.
	seteuid(getuid());
	
	// Search the individual search path first.
	
	// Finally, search the default search paths.
	if( pointerp(default_search) ) {
		i = sizeof(default_search);
		while(i--) if( file_size(default_search[i] + arg)>0 ) {
			me->start_more( read_file(default_search[i] + arg) );
			return 1;
		}
	}

	return notify_fail("没有针对这项主题的说明文件。\n");
}

int help(object me)
{
	write(@HELP
指令格式：help <主题>              例如：> help cmds
          help <函数名称>()        例如：> help call_out()

这个指令提供你针对某一主题的详细说明文件，若是不指定主题，则提供你有关
主题的文件。
HELP
	);
	return 1;
}

