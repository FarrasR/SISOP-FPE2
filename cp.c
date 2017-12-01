#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char buf[512];

void
cp(int fsource, int fdest)
{
  int n;
  while((n = read(fsource, buf, sizeof(buf))) > 0) {
    if (write(fdest, buf, n) != n) {
      printf(1, "cp: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cp: read error\n");
    exit();
  }
  return;
}
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

int main(int argc, char *argv[])
{
  int fdest, fsource;

  if(argc < 2){
    printf(1, "Usage: cp source destination \n");
    exit();
  }
  if((fsource = open(argv[1], 0)) < 0)
  {
    printf(1, "cp: cannot open %s\n", argv[1]);
    exit();
  }

  if((fdest = open(argv[2], O_CREATE | O_RDWR)) < 0)
  {
    printf(1, "cp: cannot open %s\n", argv[2]);
    exit();
  }

  if ((test_dir(argv[1])!=1) && (test_dir(argv[2])!=1))
  {
    printf(2,"not a file");
    exit();
  }

  cp(fsource, fdest);
  exit();
}
