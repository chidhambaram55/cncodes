#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/shm.h>

struct memory{
	int pid2;
};


struct memory *shmptr;


int main()
{
	
	int shmid;
	
	int key=12340;
	
	shmid=shmget(key,sizeof(struct memory),IPC_CREAT|0666);
	shmptr=(struct memory *)shmat(shmid,NULL,0);
	
	shmptr->pid2=-1;
	while(shmptr->pid2==-1);
	
	printf("%d\n",shmptr->pid2);
	
	
	while(1)
	{
		
		int flag=0;
		
		printf("do u want to send signal 1 for g1 2 for g2\n");
		scanf("%d",&flag);
		
		
		if(flag==1)
		kill(shmptr->pid2,SIGUSR1);
		else if(flag==2)
		kill(shmptr->pid2,SIGUSR2);
		
	}
	
	
	
	
	
	
	return 0;
}	
