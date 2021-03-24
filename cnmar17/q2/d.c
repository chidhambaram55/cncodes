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

int main()
{
	int fd=open("a.txt",O_RDWR);
	while(1)
	{
		char buffer[80]={0};
		fgets(buffer,80,stdin);
		//printf("B");
		if(strlen(buffer)>0)
		{
			
			write(fd,buffer,strlen(buffer));
			printf("iam B message received is %s\n",buffer);
		}
		
	}
	
	
	return 0;
}
