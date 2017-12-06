#include <syscall.h>
#include <stdio.h>
#include <string.h>


#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>
#include <xv6/fs.h>

void removethis(char*argv)
{
	int fd;
  	fd = open(argv, 0);
  	if(fd >= 0){
    	while(1)
   	unlink(argv);
 	}
}




int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    printf( "Usage: rm files...\n");
    sysexit();
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf("rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  sysexit();
}
