#include <syscall.h>
#include <stdio.h>
#include <string.h>


#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>
#include <xv6/fs.h>


int test_dir (char * path)
{
  int fd;
  fd =open (path,O_RDONLY);
  if (fd<0)
  {
    // printf("cannot open path: %s\n", path);
    // sysexit();
    // exit();
    return -1;
  }

  struct stat st;
  if(fstat(fd, &st) < 0){
    // printf("ls: cannot stat %s\n", path);
    // close(fd);
    // sysexit();
    // exit();
    return -1;
  }
  if (st.type == T_FILE)
  {
    return 1;
  }
  else if (st.type == T_DIR)
  {
    return 0;
  }
  else 
    return -1;
}

void removethis(char*argv)
{
	if(unlink(argv) < 0)
  {
    printf("rm: failed to delete:%s\n", argv);
  }
}

void wildcard (char * path)
{
  
  int fd;
  fd =open (path,0);
  if (fd<0)
  {
    printf("cannot open path: %s\n", path);
    return; 
  }
  struct dirent looker;
  char * walker;  
  char buff_src [512];
  while (read(fd, &looker, sizeof(looker)) == sizeof(looker))
  {  
    strcpy(buff_src, path);
    if (strcmp(looker.d_name, ".") ==0 || strcmp(looker.d_name, "..") ==0)
      continue;
    
    // printf("%s %s %s\n",  buff_src, buff_dest, looker.d_name);
  
    walker= buff_src + strlen(buff_src);
    if (*walker != '/') strcat(buff_src, "/");
    // printf("%s %s %s\n",  buff_src, looker.d_name);
    strcat(buff_src, looker.d_name);
    strcat(buff_src, "\0");
    // printf("%s %s %s\n",  buff_src, buff_dest, looker.d_name);
    int test=test_dir (buff_src);
    if (test == 0)
    {
      wildcard(buff_src);
    }
    else if (test == 1)
      removethis(buff_src);
    else 
    {
      printf("rm: cannot open/stat %s\n", buff_src);
      sysexit();
    }
  }
  if(unlink(path) < 0)
  {
    printf("rm: failed to delete directory:%s\n", buff_src);
  }
}

int main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    printf( "Usage: rm files...\n");
    sysexit();
  }
  if (strcmp(argv[1],"-rf")==0)
  {
    wildcard(argv[2]);
    sysexit();
  }
  for(i = 1; i < argc; i++){
    removethis(argv[i]);
  }
  sysexit();
}
