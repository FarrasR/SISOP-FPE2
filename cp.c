#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char buf[512];

char * strcat(char * source, char *string_to_be_added)
{
  char * concat;
  concat = source+ sizeof(source);
  if (*concat!='/')
    *concat++ = '/';
  memmove(concat,string_to_be_added, strlen(string_to_be_added));
  return source;
}

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
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    exit();
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
    fdest_path=strcat(fdest_path, fsource_path);
  }
  if ((test_dir(fsource_path)==0))
  {
    printf(2,"cp: omitting directory \'%s\'", fsource_path);
    exit();
  }
  
  if((fsource = open(fsource_path, 0)) < 0)
  {
    printf(1, "cp: cannot open %s\n", fsource_path);
    exit();
  }

  if((fdest = open(fdest_path, O_CREATE | O_RDWR)) < 0)
  {
    printf(1, "cp: cannot open %s\n", fdest_path);
    exit();
  }
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
  close(fsource);
  close(fdest);
  return;
}


char* global_destination;
int counter;
void wildcard (char * path, char * destination)
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
  int temp_number;
  while (read(fd, &looker, sizeof(looker)) == sizeof(looker))
  {
    
    strcpy(buff_src, path);
    strcpy(buff_dest, destination);
    
    if (strcmp(looker.name, ".") ==0 || strcmp(looker.name, "..") ==0)
      continue;
    if (looker.inum ==0) continue;
    printf(1,"counter %d\n%s %s %s\n", counter, buff_src, buff_dest, looker.name);
    counter++;


    temp_number= strlen(buff_src);
    walker= buff_src + temp_number;
    if (*walker != '/'){
       *walker++ = '/';
       temp_number++;
     }
    memmove(walker,looker.name, strlen(looker.name));
    walker=buff_src+temp_number+strlen(looker.name);
    *walker='\0';

    temp_number= strlen(buff_dest);
    walker= buff_dest + temp_number;
    if (*walker != '/'){
       *walker++ = '/';
       temp_number++;
     }
    memmove(walker,looker.name, strlen(looker.name));
    walker=buff_src+temp_number+strlen(looker.name);
    *walker='\0';



    printf(1,"counter %d\n%s %s %s\n", counter, buff_src, buff_dest);
    counter++;
    if (strcmp(global_destination, buff_src)==0)
    {
      printf(1, "cannot copy %s to it's own subdirectory \n",global_destination);
      continue;
    }

    int test=test_dir (buff_src);
    
    if (test == 0)
      wildcard(buff_src, buff_dest);
    else if (test == 1)
      cp(buff_src, buff_dest);
    else 
    {
      printf(2,"wild: cannot open %s\n", buff_src);
      exit();
    }

  }
  close(fd);
}


int main(int argc, char *argv[])
{
  counter =0;
  if(argc < 2 || argc>3){
    printf(1, "Usage: cp source destination \n");
    exit();
  }
  if (strcmp(argv[1], "*")==0)
  {
    printf(1,"wildcard\n");
    if (test_dir(argv[2])!=0)
    {
      printf(1, "Usage: mv * directory \n");
      exit();
    }
    global_destination = argv[2];
    // if (is_same_directory(".", argv[2])==-1)
    // {
    //   printf(1, "cannot move %s to it's own subdirectory \n",argv[2]);
    //   exit();
    // }
    wildcard(".", argv[2]);
    exit();
  }
  
  cp(argv[1], argv[2]);
  exit();
}
