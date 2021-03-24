#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<string.h>
#include<wait.h>
#include<sys/shm.h>

 

int main()
{ 
	
	char line[1024];
	FILE *fpin;
	fpin=popen("/home/chidha/cn/cnlabfeb3/prac2","w");
	
	while(1)
	{
		char buffer[80];
		fgets(buffer,80,stdin);
		fputs(buffer,fpin);
		fflush(fpin);
	}
		
	
	pclose(fpin);
	
	
	
	
	return 0;
	
	
}
