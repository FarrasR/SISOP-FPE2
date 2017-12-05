// #include <stdio.h>
// #include <string.h>

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

typedef struct{
	char line[20];
	char field[20];
}data;
//satu.txt dua.txt
// void strcat(char &source, char *string_to_be_added)
// {
// 	char * concat;
// 	concat = source+ sizeof(source);
// 	memmove(concat,string_to_be_added, strlen(string_to_be_added));
// 	// return source;
// }
char temp[100];
void joins(char* firstFile_path, char* secondFile_path){
	char error[]="Unsorted";
	char *firstBefore, *secondBefore;
	// char out[200];
	data first[20],second[20];
	int firstSize=0,secondSize=0,j=0,i=0,lenField,lenLine,idx;
	int handler;
	int firstFile, secondFile;
	firstFile =open (firstFile_path,0);
	secondFile=open (secondFile_path,0);

	if(firstFile<0||secondFile<0){
		printf(2,"File doesn't exist");
		exit();
	}
	while((handler = read(firstFile, temp, sizeof(temp))) > 0) {
		// (fgets(temp,100,firstFile)!=NULL){
			printf(2,"get read\n");
		j=0;
		idx=0;
		while(temp[j]!=' '&&temp[j]!='\0'&&temp[j]!='\n'){
			first[i].field[j]=temp[j];
			++j;
		}
		lenLine=strlen(temp);
		lenField=strlen(first[i].field);
		idx=0;
		for(;lenField<lenLine;lenField++){
			if(temp[lenField]=='\n')break;
			first[i].line[idx]=temp[lenField];
			++idx;
		}
		++i;
	}
	close(firstFile);
	if(handler < 0){
	    printf(2, "read error\n");
	    exit();
  	}
	firstSize=i;
	i=0;
	temp[0]=0;
	while((handler = read(secondFile, temp, sizeof(temp))) > 0){
		//(fgets(temp,100,secondFile)!=NULL){
		j=0;
		while(temp[j]!=' '&&temp[j]!='\0'&&temp[j]!='\n'&&j<strlen(temp)){
			second[i].field[j]=temp[j];
			++j;
		}
		lenLine=strlen(temp);
		lenField=strlen(second[i].field);
		idx=0;
		for(;lenField<lenLine;lenField++){
			if(temp[lenField]=='\n')break;
			second[i].line[idx]=temp[lenField];
			++idx;
		}
		++i;
	}
	close(secondFile);
	secondSize=i;
	// strcpy(firstBefore,first[0].field);
	// strcpy(secondBefore,second[0].field);
	firstBefore=first[0].field;
	secondBefore=second[0].field;
	int unsortedIdx[20];
	idx=0;
	for (i=0;i<20;i++)
		unsortedIdx[i]=0;
	for(i=0;i<firstSize;i++){
		if(strcmp(firstBefore,first[i].field)!=1){
			int x=0;
			while((strcmp(first[i].field,second[x].field)==1)&&(x<secondSize)){
				if(strcmp(secondBefore,second[x].field)==1){
					if(!unsortedIdx[x]){
						// strcpy(out,error);
						printf(2,"%s\n",error);
					}
					while((strcmp(secondBefore,second[x].field)!=-1)&&(x<secondSize)){
						unsortedIdx[x]=1;
						++x;
					}
				}
				else{
					unsortedIdx[x]=1;
					// strcpy(secondBefore,second[x].field);
					secondBefore=second[x].field;
					++x;
				}
			}
			while(strcmp(first[i].field,second[x].field)==0){
				printf(2,"%s%s%s\n",first[i].field,first[i].line,second[x].line);
				// printf(2,"panic\n");
				//system(echo $out);
				++x;
			}
			// strcpy(firstBefore,first[i].field);
			firstBefore=first[i].field;
		}
		else{
			// strcpy(out,error);
			printf(2,"%s\n",error);
			//system(echo $out);
			// while(strcmp(firstBefore,first[i].field)!=-1){
			// 	++i;
			// }
			// --i;
		}
	}
	// printf(2,"get compare\n");
	exit();
}
int main(int argc, char* argv[]){
	// int firstFile, secondFile;
	//scanf("%s %s",firstPath, secondPath);
	// char t[100];
	if (argc<3||argc>3) 
	{
		printf(2,"Usage : join file1 file2..\n");
		// int i;
		// printf(1,"%d\n", argc);
		// for (i=1; i<argc;i++)
		// 	printf(1,"%s\n", argv[i]);
		exit();
	}
	joins(argv[1], argv[2]);
	exit();
}
