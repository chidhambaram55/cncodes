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
#include <sys/poll.h>
#include <sys/time.h>
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
int c,pid,c2;

gid_t gid1=100;
gid_t gid2=200;
int totalsignals=0;
void handler(int signo)
{
	if(signo==SIGUSR1&&c>0)
	{
		printf("signal received for g1\n");
		flagr=1;
		//kill(c,SIGCONT);
		//kill(c2,SIGCONT);
		totalsignals++;
		killpg(gid1,SIGCONT);
		killpg(gid2,SIGSTOP);
		  	
	}
	else if(signo==SIGUSR2&&c>0)
	{
		printf("signa received for g2\n");
		flagr=2;
		//kill(c,SIGSTOP);
		//kill(c2,SIGSTOP);
		 totalsignals++;
		 killpg(gid1,SIGSTOP);
		 killpg(gid2,SIGCONT);
	}
}
  
int main()
{
  
	 
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler);
	 
	int shmid;
	int key=12340;
	
	
	shmid=shmget(key,sizeof(struct memory),IPC_CREAT|0666);
	shmptr=(struct memory *)shmat(shmid,NULL,0);
	
	
	//
	int shmid2;
	int key2=12354;
	shmid2=shmget(key2,sizeof(struct memory2),IPC_CREAT|0666);
	shmptrb=(struct memory2 *)shmat(shmid2,NULL,0);
	
	
	
	shmptr->pid2=-1;
	pid=getpid();
	shmptr->pid2=getpid();
	printf("%d\n",pid);
	int pip1[2];
 	pipe(pip1);
 	c=fork();
 	
 	
 	
 	if(c>0)
 	{
 		// parent
 		int fd;
 		close(pip1[0]);
	
		char *myfifo="/home/chidha/cn/cnlabfeb3/fromc1";
		
		mkfifo(myfifo,0666);
		//
		int fd2;
	
		char *myfifo2="/home/chidha/cn/cnlabfeb3/fromc2";
	
		mkfifo(myfifo2,0666);
		//
		
		int pip2[2];
		pipe(pip2);
		c2=fork();
		
		if(c2>0)
		{
			close(pip2[0]);
			FILE *fpin,*fpin2;
			shmptrb->pidb=-1;
			fpin=popen("/home/chidha/cn/cnlabfeb3/B","w");
			fpin2=popen("/home/chidha/cn/cnlabfeb3/A","w");
			while(shmptrb->pidb==-1);
			
			
			//		
			struct pollfd pfds[2];
			//
			
			
			while(1)
			{
			
			
				//
				fd=open(myfifo,O_RDONLY|O_NONBLOCK);
				fd2=open(myfifo2,O_RDONLY|O_NONBLOCK);
				pfds[0].fd=fd;
				pfds[1].fd=fd2;
				pfds[0].events=POLLIN;
				pfds[1].events=POLLIN;
				
				poll(pfds,2,-1);
				char buffer[1024]={0};
				int ch;
				if(pfds[0].revents&&POLLIN)
				{
					ch=read(fd,buffer,1024);
				}
		
				if(pfds[1].revents&&POLLIN)
				{
					ch=read(fd2,buffer,1024);
				}
				
				//
		
				//ch1  fd=open(myfifo,O_RDONLY);
	
				//ch3 char buffer[80]={0};
				
				
				//ch2 int ch=read(fd,buffer,80);
				printf("total signals are %d\n",totalsignals*3);
				printf("%s\n",buffer);
				close(fd);
				close(fd2);
				if(ch>0&&flagr==1)
				{
					write(pip1[1],buffer,ch);
					write(pip2[1],buffer,ch);
				}
				else if(ch>0&&flagr==2)
				{
					//char buffer[80];
					//fgets(buffer,80,stdin);
					fputs(buffer,fpin);
					fflush(fpin);
					fputs(buffer,fpin2);
					fflush(fpin2);
				}	
 
 			 }
 			 wait(NULL);
 			 wait(NULL);
 		}
 		else
 		{
 			close(pip2[1]);
 			setgid(gid1);
 			//int gid=getgid();
 			//printf("child2 belongs to group
 			while(1)
 			{
 				//printf("iam child\n");
 			
 				char buffer[80]={0}	;
 				int ch=read(pip2[0],buffer,80);
 				if(ch>0)
 				{
 					printf("from child2 %s\n",buffer);
 				}
 			
 			}	
 		
 		
 		}
 	}
 	else
 	{
 		close(pip1[1]);
 		// child
 		setgid(gid1);
 		while(1)
 		{
 			//printf("iam child\n");
 			
 			char buffer[80]={0};
 			int ch=read(pip1[0],buffer,80);
 			if(ch>0)
 			{
 				printf("from child11 %s\n",buffer);
 			}
 			
 		}	
 		
 	}
	
	return 0;
	
	
}










 





