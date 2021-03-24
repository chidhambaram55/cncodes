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
struct memory2{
	int pidb;
};

struct memory2 *shmptrb;
 gid_t gid2=200;
int main()
{
	 
	//
	int shmid2;
	int key2=12354;
	shmid2=shmget(key2,sizeof(struct memory2),IPC_CREAT|0666);
	shmptrb=(struct memory2 *)shmat(shmid2,NULL,0);
	setgid(200);
	shmptrb->pidb=getpid();
	while(1)
	{
		char buffer[80]={0};
		fgets(buffer,80,stdin);
		//printf("B");
		if(strlen(buffer)>0)
		{
			
		
			printf("iam A message received is %s\n",buffer);
		}
		
	}
	
	
	return 0;
}
