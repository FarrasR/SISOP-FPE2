// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <string.h>
// #include <dirent.h>

// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fs.h"

#include <syscall.h>
#include <stdio.h>
#include <string.h>

#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>


#define space 10

char * get_filename (char * path)
{
	char * buff;
	for (buff = path+strlen(path); *buff!='/' && buff>=path; buff-- );
	buff+=1;
	return buff;
}

char * get_space (char * path)
{
	static char buf[space+1];
	
	// int flexible_space = (strlen(path)/10 +1) * 10;
	int flexible_space = space;
	int flexible_length=strlen(path);
	if (strlen(path) > 13) 
	{
		memmove(buf, path, 12);
		flexible_length = 12;
		flexible_space=20;
		memset(buf+flexible_length, ' ', flexible_space- flexible_length);
		return path;
	}
	memmove(buf, path, strlen(path));
  	memset(buf+flexible_length, ' ', flexible_space- flexible_length);
	return buf;
}

void ls (char *path )
{
	int fd;
	fd =open (path,0);
	if (fd<0)
	{
		printf("cannot open path: %s\n", path);
		return;	
	}
	struct stat file_status;
	if (fstat(fd, &file_status))
	{
		printf("cannot stat path: %s\n", path);
		return;
	}
	if(file_status.type ==T_DIR )
	{		
		struct dirent looker;
		while (read(fd, &looker, sizeof(looker)) == sizeof(looker))
		{
			if (looker.d_ino ==0) continue;
			printf("%s", get_space(looker.d_name));
		}
	}
	else 
	{
		printf("%s\n", get_space(get_filename(path)));
	}
	printf("\n");
	close(fd);
	return;
}


int main(int argc, char *argv[])
{
  int i;
  if(argc < 2){
    ls(".");
    sysexit();
  }
  for (i=1; i<argc; i++)
   ls(argv[i]);
  sysexit();
  // exit();
  // for(i=1; i<argc; i++)
  //   ls(argv[i]);
  // return 0;
}
