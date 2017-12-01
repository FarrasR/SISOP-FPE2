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
      printf(1, "mv: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "mv: read error\n");
    exit();
  }
  return;
}

int main(int argc, char *argv[])
{
  int fdest, fsource;

  if(argc < 2){
    printf(1, "Usage: mv source destination \n");
    exit();
  }
  if((fsource = open(argv[1], 0)) < 0)
  {
    printf(1, "mv: cannot open %s\n", argv[1]);
    exit();
  }

  if((fdest = open(argv[2], O_CREATE | O_RDWR)) < 0)
  {
    printf(1, "mv: cannot open %s\n", argv[2]);
    exit();
  }

  cp(fsource, fdest);
  if(unlink(argv[1]) < 0){
    printf(2, "rm: %s failed to delete\n", argv[1]);
  }
  exit();
}
