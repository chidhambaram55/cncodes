#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


int main()
{

	int fd;
	
	char *myfifo="/home/chidha/cn/cnlabfeb3/fromc1";
	
	mkfifo(myfifo,0666);
	
 
	
	
	while(1)
	{
		fd=open(myfifo,O_WRONLY|O_NONBLOCK);
	
	
		char buffer[80]={0};
		fgets(buffer,80,stdin);
		
		if(strlen(buffer)>0)
		{
		
		write(fd,buffer,strlen(buffer));
		
		
		}
		close(fd);
	}
	
	
	
	return 0;
	
	
	
}
	
	
	
