// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <string.h>
// #include <dirent.h>

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


char * get_filename (char * path)
{
	char * buff;
	for (buff = path+strlen(path); *buff!='/' && buff>=path; buff-- );
	buff+=1;
	return buff;
}

void ls (char *path )
{
	int fd;
	fd =open (path,0);
	struct stat file_status;
	char buffer[512];
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
			if (de.inum ==0) continue
			printf(1,"%s\n", looker.name);
		}
	}
	else 
	{
		printf(1,"%s\n", get_filename(path));
	}

}


int main(int argc, char *argv[])
{
  int i;
  if(argc < 2){
    ls(".");
    return 0;
  }
  for (i=1; i<argc; i++)
   ls(argv[i]);


  return 0;
  
  // for(i=1; i<argc; i++)
  //   ls(argv[i]);
  // return 0;
}