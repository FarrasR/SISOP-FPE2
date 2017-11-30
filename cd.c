#include "syscall.h"
#include "fcntl.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char *argv[])
{
	if (argc>1)
	{
		printf(1, "Usage: cd directory\n");
	}
	int fd;
	fd =open (argv[1],O_RDONLY);
	if (fd<0)
	{
		printf(2,"cannot open path: %s\n", path);
		return;	
	}

	struct stat st;
	if(fstat(fd, &st) < 0){
	  printf(2, "ls: cannot stat %s\n", path);
	  close(fd);
	  return;
	}
	if (st.type == T_FILE)
	{
		printf(2,"not a directory");
		return;	
	}
	
	SYS_chdir(argv[1]);
}