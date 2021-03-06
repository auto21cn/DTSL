// cpdir.c
// by dsm @Jianghu 5/7/99
 
inherit F_CLEAN_UP;
int do_copy(object me,string src,string dst);
//private void confirm_dest(string yn, object ob,string dst);
int main(object me, string arg)
{
	string src,dst;
	mixed *file; 

	seteuid(geteuid(me));
	if (!arg || sscanf(arg, "%s %s", src, dst)!=2 ) return
		notify_fail("指令格式: cpdir <源目录> <目标目录> \n");

	src = resolve_path(me->query("cwd"), src);
	dst = resolve_path(me->query("cwd"), dst);

	if( file_size(src)!=-2 ) return notify_fail("没有源目录\n");

	if( src[strlen(src)-1] != '/' ) src += "/"; 
	file = get_dir(src,-1); 
	if( !sizeof(file) ) return notify_fail("源目录是空的。\n"); 

	if( file_size(dst)==-2 ) {
        	write("目标目录已存在,同名文件将会被覆盖,是否继续[y/n]?");
        	input_to( "confirm_dest",1,me,src,dst );
	}else do_copy(me,src,dst);
	return 1;
}
 
private void confirm_dest(string yn, object me,string src,string dst)
{
	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("程序结束.\n");
		return;
	}else do_copy(me,src,dst);
}

int do_copy(object me,string src,string dst)
{
	int i,j;
	mixed *file; 

	file = get_dir(src,-1); 

	mkdir(dst);
	if( dst[strlen(dst)-1] != '/' ) dst += "/"; 

	for(i=0, j = sizeof(file); i<j; i++) 
	{ 
		cp(src+file[i][0], dst+file[i][0]);
	} 
	write("ok.\n");
	return 1; 
} 
 
int help(object me)
{
  write(@HELP
指令格式 : cpdir <源目录> <目标目录>
 
HELP
    );
    return 1;
}
