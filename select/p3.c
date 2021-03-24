#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/select.h>
#include<string.h>

#include<fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h> 

int main()
{
	char *myfifo1="/home/chidha/cn/select/fifo2";
		
	mkfifo(myfifo1,0666);
	int fd=open(myfifo1,O_WRONLY|O_NONBLOCK);
	while(1)
	{
		
		char buffer[80]={0};
		fgets(buffer,80,stdin);
		
		if(strlen(buffer)>0)
		{
		
		write(fd,buffer,strlen(buffer));
		
		
		}
		
	}
	close(fd);
	return 0;	
}
		
