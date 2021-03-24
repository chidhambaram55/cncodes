#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <sys/shm.h> 

struct livem{
int c;
};

struct livem *chmptr;
int main()
{

	int fd;
	
	char *myfifo="/home/chidha/cn/cnmar17/q2/fifo1";
	
	mkfifo(myfifo,0666);
	
 	int ckey = 12559; 

	// shared memory create 
	int chmid = shmget(ckey, sizeof(struct livem), IPC_CREAT | 0666); 

	// attaching the shared memory 

	chmptr = (struct livem*)shmat(chmid, NULL, 0); 

	
	
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
	
	
	
