// #include <stdio.h>
// #include <string.h>

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

typedef struct{
	char line[100];
	char field[100];
}data;
//satu.txt dua.txt
void join(int firstFile, int secondFile){
	char error[]="Unsorted";
	char temp[100];
	char firstBefore[100], secondBefore[100];
	char out[200];
	data first[100],second[100];
	int firstSize=0,secondSize=0,j=0,i=0,lenField,lenLine,idx;
	int handler;
	while((handler = read(firstFile, temp, sizeof(temp))) > 0) {
		// (fgets(temp,100,firstFile)!=NULL){
		j=0;
		idx=0;
		while(temp[j]!=' '&&temp[j]!='\0'&&temp[j]!='\n'){
			first[i].field[j]=temp[j];
			++j;
		}
		lenLine=strlen(temp);
		lenField=strlen(first[i].field);
		idx=0;
		for(lenField;lenField<lenLine;lenField++){
			if(temp[lenField]=='\n')break;
			first[i].line[idx]=temp[lenField];
			++idx;
		}
		++i;
	}
}
int main(int argc, char* argv){
	int firstFile, secondFile;
	//scanf("%s %s",firstPath, secondPath);
	firstFile =open (argv[1],0);
	secondFile=open(argv[2],0);
	if(firstFile<0||secondFile<0){
		printf(2,"File doesn't exist");
		exit();
	}
	// char t[100];
	join(firstFile, secondFile);
	return 0;
}
