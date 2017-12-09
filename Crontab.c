//crontab
#include <stdio.h>
#include <time.h>
#include <string.h>
time_t wow[10];
int timeIsRight(int *min, int *hour, int *dayMonth, int *month, int *dayWeek, int minSize, int hourSize, int dayMonthSize, int monthSize, int dayWeekSize, int line){
	time_t now;
	time(&now);
	struct tm *timeInfo=localtime(&now);
	struct tm *timeMade=localtime(&wow[line]);
	int i,true,d;
	if(min[0]!=69){
		true=0;
		for(i=0;i<minSize;i++){
			if(min[i]<0){
				d=timeInfo->tm_min-timeMade->tm_min;
				if(d<0)d+=60;
				if(d==min[i])true=1;
			}
			else if(timeInfo->tm_min==min[i])true=1;
		}
		if(!true)return 0;
	}
	if(hour[0]==69){
		for(i=0;i<hourSize;i++){
			if(hour<0){
				d=timeInfo->tm_hour-timeMade->tm_hour;
				if(d<0)d+=24;
				if(d==hour[i])true=1;
			}
			else if(timeInfo->tm_hour==hour[i])true=1;
		}
		if(!true)return 0;
	}
	if(dayMonth[0]==69){
		for(i=0;i<dayMonthSize;i++){
			if(dayMonth<0){
				
			}
			else if(timeInfo->tm_mday==dayMonth[i])true=1;
		}
		if(!true)return 0;
	}
	if(month[0]==69){
		true=0;
		for(i=0;i<monthSize;i++){
			if(month[i]<0){
				
			}
			else if(timeInfo->tm_mon==month)true=1;
		}
		if(!true)return 0;
	}
	if(dayWeek[0]==69){
		true=0;
		for(i=0;i<dayWeekSize;i++){
			if(dayWeek[i]<0){
				
			}
			else if(timeInfo->tm_wday==dayWeek[i])true=1;
		}
		if(!true)return 0;
	}
	time(&wow);
	return 1;
}
int main(void){
	FILE *cron,*cronBackup;
	char inp[175],inpBackup[175];
	char command[100];
	char buff[25];
	int min[10],hour[10],dayMonth[10],month[10],dayWeek[10];
	int minSize,hourSize,dayMonthSize,monthSize,dayWeekSize;
	int i, j, length, idx, t, line, flag[10];
	memset(flag,0,sizeof(flag));
	while(1){
		cron=fopen("cron.txt","r");
		cronBackup=fopen("cronBackup.txt","r");
		t=0;
		line=1;
		idx=0;
		minSize=0;hourSize=0;dayMonthSize=0;monthSize=0;dayWeekSize=0;
		while(fgets(inp,175,cron)!=NULL){
			fgets(inpBackup,1075,cronBackup);
			length=strlen(inp);
			memset(buff,'\0',sizeof(buff));
			memset(command,'\0',sizeof(min));
			j=0;
			for(i=0;i<length;i++){
				if((inp[i]==',')||(t==5)||(inp[i]==' ')){
					switch(t){
						case 0:
							if(strcmp(buff,"*")!=0){
								if(inp[i-1]!='/')min[minSize]=atoi(buff);
								else min[minSize]=-(atoi(buff));
								++minSize;
							}
							else min[minSize]=69;
							break;
						case 1:
							if(strcmp(buff,"*")!=0){
								if(inp[i-1]!='/')hour[hourSize]=atoi(buff);
								else hour[hourSize]=-(atoi(buff));
								++hourSize;
							}
							else hour[hourSize]=69;
							break;
						case 2:
							if(strcmp(buff,"*")!=0){
								if(inp[i-1]!='/')dayMonth[dayMonthSize]=atoi(buff);
								else dayMonth[dayMonthSize]=-(atoi(buff));
								++dayMonthSize;
							}
							else dayMonth[dayMonthSize]=69;
							break;
						case 3:
							if(strcmp(buff,"*")!=0){
								if(inp[i-1]!='/')month[monthSize]=atoi(buff);
								else month[monthSize]=-(atoi(buff));
								++monthSize;
							}
							else month[monthSize]=69;
							break;
						case 4:
							if(strcmp(buff,"*")!=0){
								if(inp[i-1]!='/')dayWeek[dayWeekSize]=atoi(buff);
								else dayWeek[dayWeekSize]=-(atoi(buff));								
								++dayWeekSize;
							}
							else dayWeek[dayWeekSize]=69;
							break;
						case 5:
							for(i;i<length;i++){
								command[j]=inp[i];
								++j;
							}
							break;
						default:
							break;
					}
					if(inp[i]==' ')++t;
					j=0;
					memset(buff,'\0',sizeof(buff));
				}
				else if(inp[i]!='/'){
					buff[j]=inp[i];
					++j;
				}
			}
			if(strcmp(inp,inpBackup)==0){
				if((flag[line]==0) && timeIsRight(min, hour, dayMonth, month, dayWeek, minSize, hourSize, dayMonthSize, monthSize, dayWeekSize, line)){
					//system(command);
					flag[line]=1;
				}
				else if((flag[line]==1)&&(!timeIsRight(min, hour, dayMonth, month, dayWeek, minSize, hourSize, dayMonthSize, monthSize, dayWeekSize, line)))flag[line]=0;
			}
			else{
				flag[line]=0;
				time(&wow[line]);
				if(timeIsRight(min, hour, dayMonth, month, dayWeek, minSize, hourSize, dayMonthSize, monthSize, dayWeekSize, line));//system("command");
			}
			++line;
		}
		fclose(cron);
		fclose(cronBackup);
		line=0;
		//system(rm cronBackup.txt);
		//system(cp cron.txt cronBackup.txt);
	}
	return 0;
}
