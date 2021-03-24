// S.c feb9
//start
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
struct memory{
	int pid2;
};

struct memory *shmptr;

struct memory2{
	int pidb;
};

struct memory2 *shmptrb;
int fl=0;
int flagr=0;

void handler(int signo)
{
	if(signo==SIGUSR1)
	{
		printf("signal received for g1\n");
		kill(shmptrb->pidb,SIGSTOP);
		fl=1;	
	}
	else if(signo==SIGUSR2)
	{
		printf("signal received for g2\n");
		kill(shmptrb->pidb,SIGCONT);
		fl=2;
	}
}
 
void rhandler(int signo)
{
	if(signo==SIGSTOP)
	{
		flagr=1;
		
		printf("read signal sent to g1\n");
	}
	else if(signo==SIGHUP)
	{
		flagr=2;
		printf("readsignal sent to g2\n");
	}
}




int main()
{
  
	signal(SIGSTOP,rhandler);
	signal(SIGHUP,rhandler);
	
	
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	  
			int shmid;
			int key=12340;
	
	
			shmid=shmget(key,sizeof(struct memory),IPC_CREAT|0666);
			shmptr=(struct memory *)shmat(shmid,NULL,0);
			shmptr->pid2=-1;
			int pid=getpid();
			shmptr->pid2=getpid();
			
		/*	int shmidb;
			int keyb=12678;
			shmidb=shmget(keyb,sizeof(struct memory2),IPC_CREAT|0666);
			shmptrb=(struct memory2 *)shmat(shmidb,NULL,0);
			shmptrb->pidb=-1;
			
			
			
			while(shmptrb->pidb==-1);*/
			
			printf("%d\n",pid);
			//printf("%d\n",shmptrb->pidb);
	
	
			int fdc1;
	
			char *myfifo="/home/chidha/cn/cnlabfeb3/fromc1";
	
			mkfifo(myfifo,0666);
	  
			while(1)
			{ 
				 
				 
				// printf("%d",fl);
				//while(fl==2)
				{
					
					//printf("%d",fl); 
					int pids=getpid();
			
					char buffer[80]={0};	
					fdc1=open(myfifo,O_RDONLY);
					//printf("hiii");
					read(fdc1,buffer,80);
					 close(fdc1);
					if(strlen(buffer)>0)
					{
						FILE *b=popen("/home/chidha/cn/cnlabfeb3/B","w");
						 fputs(buffer,b);
						 
						 fclose(b);
						 printf("%s\n",buffer);
					//	 break;
 
					}
			
					//kill(shmptrb->pidb,SIGSTOP);
  
				//	kill(pids,SIGHUP);
				}
			}
			
			 
 
	
	return 0;
	
	
}
// end









 





