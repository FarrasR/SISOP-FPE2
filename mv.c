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
    printf("cannot open path: %s\n", path);
    sysexit();
    // exit();
  }

  struct stat st;
  if(fstat(fd, &st) < 0){
    printf("ls: cannot stat %s\n", path);
    close(fd);
    sysexit();
    // exit();
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
    strcat(destination, source);
    // memmove(tester, source, strlen(source));
  }
  if((fsource = open(source, 0)) < 0) 
  {
    printf("mv: cannot open %s\n", source);
    sysexit();
    // exit();
  }

  if((fdest = open(destination, O_CREAT | O_RDWR)) < 0)
  {
    printf("mv: cannot creat %s\n", destination);
    sysexit();
    // exit();
  }

  while((n = read(fsource, buf, sizeof(buf))) > 0) 
  {
    if (write(fdest, buf, n) != n) 
    {
      printf("mv: write error\n");
      sysexit();
      // exit();
    }
  }
  close(fdest);
  close(fsource);
  if(n < 0)
  {
    printf("mv: read error\n");
    sysexit();
  }
  
  if(unlink(source) < 0)
  {
    printf("rm: %s failed to delete\n", source);
  }
}

char * global_destination;
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

int main(int argc, char *argv[])
{
  if(argc < 2){
    printf("Usage: mv source destination \n");
    sysexit();
    // exit();
  }
  if (strcmp(argv[1], "*")==0)
  {
    // printf("wildcard\n");
    if (test_dir(argv[2])!=0)
    {
      printf("Usage: mv * directory \n");
      sysexit();
      // exit();
    }
    global_destination = argv[2];
    // if (is_same_directory(".", argv[2])==-1)
    // {
    //   printf(1, "cannot move %s to it's own subdirectory \n",argv[2]);
    //   exit();
    // }
    wildcard(".", argv[2]);
    sysexit();
    // exit();
  }
  cp(argv[1], argv[2]);
  sysexit();
  // exit();
}
