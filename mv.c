#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char buf[512];

int test_dir (char * path)
{
  int fd;
  fd =open (path,O_RDONLY);
  if (fd<0)
  {
    printf(2,"cannot open path: %s\n", path);
    exit();
  }

  struct stat st;
  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    exit();
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


void cp(char * source, char * destination)
{
  int n;
  int fdest, fsource;
  if ((test_dir(destination)!=1))
  {
    char * tester = destination +strlen(destination);
    if (*tester != '/')
    {
      *tester++ = '/';
    }
    memmove(tester, source, strlen(source));
  }
  if((fsource = open(source, 0)) < 0) 
  {
    printf(1, "mv: cannot open %s\n", source);
    exit();
  }

  if((fdest = open(destination, O_CREATE | O_RDWR)) < 0)
  {
    printf(1, "mv: cannot creat %s\n", destination);
    exit();
  }

  if(unlink(source) < 0)
  {
    printf(2, "rm: %s failed to delete\n", source);
  }
  while((n = read(fsource, buf, sizeof(buf))) > 0) 
  {
    if (write(fdest, buf, n) != n) 
    {
      printf(1, "mv: write error\n");
      exit();
    }
  }
  if(n < 0)
  {
    printf(1, "mv: read error\n");
    exit();
  }
}

void wildcard_runner (char * path, char * destination)
{
  char buff_src [512];
  char buff_dest [512];
  int fd;
  fd =open (path,0);
  if (fd<0)
  {
    printf(1,"cannot open path: %s\n", path);
    return; 
  }
  struct dirent looker;
  char * walker;
  while (read(fd, &looker, sizeof(looker)) == sizeof(looker))
  {
    strcpy(buff_src, path);
    strcpy(buff_dest, destination);

    if (looker.inum ==0) continue;

    walker= buff_src + strlen(buff_src);
    if (*walker != '/') *walker++ = '/';
    memmove(walker,looker.name, strlen(looker.name));
    walker= buff_dest + strlen(buff_dest);
    if (*walker != '/') *walker++ = '/';
    memmove(walker,looker.name, strlen(looker.name));

    if (test_dir (buff_src) == 0)
      wildcard_runner(buff_src, buff_dest);
    else if (test_dir (buff_src) == 1)
      cp(buff_src, buff_dest);
    else 
    {
      printf(2,"cannot open %s\n", buff_dest);
      exit();
    }

  }
  close(fd);
}

void wildcard (char * path, char * destination)
{
  if (test_dir(destination)!= 0)
  {
    printf(2,"syntax: mv * directory\n" );
  }
}





int main(int argc, char *argv[])
{

  if(argc < 2){
    printf(1, "Usage: mv source destination \n");
    exit();
  }
  exit();
}
