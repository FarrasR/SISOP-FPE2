#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

int main (int argc, char *argv[]) {
	int fd0,fd1,n=0;

	if(argc <= 2) {
		printf(1, "Need 2 arguments\n");
		exit();
	}

	if((fd0 = open(argv[1], O_RDONLY)) < 0) {
		printf(1,"cp: can't open %s\n",argv[1]);
		exit();
	}

	struct stat st;
	fstat(fd0,&st);
	if(st.type == T_DIR) {
		printf(1,"src is a dir. List Files:\n");

	char com[128] ={};
	strcpy(com,argv[2]);
	int len1 = strlen(argv]1]);
	int len2 = strlen(argv[2]);

	if(argv[2][len2-1]=='/') {
		int i = len1-1;
		for(; i>=0; i--) {
			if(argv[1][i]=='/') break;
		i++;
		strcpy(&com[len2],&argv[1][i]);

	if((fd1 = open(com,O_CREATE|O_RDWR)) < 0) {
		printf(1,"cp: can't open %s\n",argv[2]);
		exit();
	}
	printf(1,"BERHASIL\n");
	while ( ( n = read(fd0,buf,sizeof(buf))) > 0) {
		write(fd1,buf,n);
	}
	close(fd0);
	close(fd1);
	exit();
} 

char* fmtname(char *path) {
	static char buf[DIRSIZ+1];
