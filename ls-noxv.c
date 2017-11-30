#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
#include <string.h>
// #include <sys/wait.h>
#include <dirent.h>
// #include <sys/wait.h>
// #include <errno.h>
// #include <unistd.h>
// #include <syslog.h>

char * get_filename (char * path)
{
	char * buff;
	for (buff = path+strlen(path); *buff!='/' && buff>=path; buff-- );
	buff+=1;
	return buff;
}

void ls (char *path )
{
	struct stat file_status;
	if (stat(path, &file_status))
	{
		printf("cannot stat path: %s\n", path);
	}
	if(file_status.st_mode & S_IFDIR )
	{
		DIR * walker=opendir(path);
		struct dirent * looker;
		while (looker = readdir(walker)!=NULL)
		{
			printf("%s\n", looker->d_name);
		}
		closedir(walker);
	}
	else 
	{
		printf("%s\n", get_filename(path));
	}

}


int main(int argc, char *argv[])
{
  int i;

  if(argc < 1){
    ls(".");
    return 0;
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  return 0;
}