// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fs.h"
// #include "fcntl.h"

#include <syscall.h>
#include <stdio.h>
#include <string.h>


#include <xv6/stdio.h>
#include <xv6/dirent.h>
#include <xv6/stat.h>
#include <xv6/fcntl.h>
#include <xv6/fs.h>

char buf[512];


int test_dir (char * path)
{
  int fd;
  fd =open (path,O_RDONLY);
  if (fd<0)
  {
    return -1;
  }

  struct stat st;
  if(fstat(fd, &st) < 0){
    printf("ls: cannot stat %s\n", path);
    close(fd);
    sysexit();
    // exit();
  }
  close(fd);
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


void cp(char* fsource_path, char* fdest_path)
{
  int fdest, fsource;
  if (test_dir(fdest_path)==0)
  {
    char * test_slash = fdest_path +strlen(fdest_path);
    if (*test_slash!='/') *test_slash++ = '/';
    strcat(fdest_path, fsource_path);
  }
  if ((test_dir(fsource_path)==0))
  {
    printf("cp: omitting directory \'%s\'", fsource_path);
    sysexit();
    // exit();
  }
  
  if((fsource = open(fsource_path, 0)) < 0)
  {
    printf("cp: cannot open %s\n", fsource_path);
    sysexit();
    // exit();
  }

  if((fdest = open(fdest_path, O_CREAT | O_RDWR)) < 0)
  {
    printf("cp: cannot open %s\n", fdest_path);
    sysexit();
    // exit();
  }
  int n;
  while((n = read(fsource, buf, sizeof(buf))) > 0) {
    if (write(fdest, buf, n) != n) {
      printf("cp: write error\n");
      sysexit();
      // exit();
    }
  }
  if(n < 0){
    printf("cp: read error\n");
    sysexit();
    // exit();
  }
  close(fsource);
  close(fdest);
  return;
}


char* global_destination;
// int counter;
void wildcard (char * path, char * destination)
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
  // int temp_number;
  char buff_src [512];
  char buff_dest [512];  
  while (read(fd, &looker, sizeof(looker)) == sizeof(looker))
  {  
    strcpy(buff_src, path);
    strcpy(buff_dest, destination);
    
    if (strcmp(looker.d_name, ".") ==0 || strcmp(looker.d_name, "..") ==0)
      continue;
    // if (looker.inum ==0) continue;
    printf("%s %s %s\n",  buff_src, buff_dest, looker.d_name);
    // counter++;


    // temp_number= strlen(buff_src);
    walker= buff_src + strlen(buff_src);
    if (*walker != '/'){
       // *walker++ = '/';
       // temp_number++;
       strcat(buff_src, "/");
     }
    

    // temp_number= strlen(buff_dest);
    walker= buff_dest + strlen(buff_dest);
    if (*walker != '/'){
       // *walker++ = '/';
      strcat(buff_dest, "/");
     }

    printf("%s %s %s\n",  buff_src, buff_dest, looker.d_name);
    strcat(buff_src, looker.d_name);
    strcat(buff_src, "\0");
    strcat(buff_dest, looker.d_name);
    strcat(buff_dest, "\0");

    printf("%s %s %s\n",  buff_src, buff_dest, looker.d_name);
    if (strcmp(global_destination, buff_src)==0)
    {
      printf("cannot copy %s to it's own subdirectory \n",global_destination);
      continue;
    }

    int test=test_dir (buff_src);
    
    if (test == 0)
    {
      mkdir(buff_dest);
      wildcard(buff_src, buff_dest);
    }
    else if (test == 1)
      cp(buff_src, buff_dest);
    else 
    {
      printf("cp: cannot open %s\n", buff_src);
      sysexit();
    }
    // walker= buff_src;
    // memmove(walker, "0", sizeof(buff_src));
    // walker= buff_dest;
    // memmove(walker,"0", sizeof(buff_dest));
  }

  close(fd);
}


int main(int argc, char *argv[])
{
  // counter =0;
  if(argc < 2 || argc>3){
    printf("Usage: cp source destination \n");
    sysexit();
  }
  if (strcmp(argv[1], "*")==0)
  {
    if (test_dir(argv[2])!=0)
    {
      printf("Usage: mv * directory \n");
      sysexit();
    }
    global_destination = argv[2];
    wildcard(".", argv[2]);
    sysexit();
  }
  
  cp(argv[1], argv[2]);
  sysexit();
}
