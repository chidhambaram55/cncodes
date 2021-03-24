#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/select.h>
#include<string.h>
#include<fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include<sys/ipc.h>
#include<sys/msg.h>
#include <sys/shm.h> 

struct livem{
int c;
};

struct msgbuffer{
	long msgtype;
	char msgbuffer[80];
};
struct livem *chmptr;
 



int main()
{

	int ckey = 12559; 

	// shared memory create 
	int chmid = shmget(ckey, sizeof(struct livem), IPC_CREAT | 0666); 

	// attaching the shared memory 

	chmptr = (struct livem*)shmat(chmid, NULL, 0); 

	chmptr->c=0;
	
	 
	char *myfifo1="/home/chidha/cn/cnmar17/q2/fifo1";
		
	mkfifo(myfifo1,0666);
	
	char *myfifo2="/home/chidha/cn/cnmar17/q2/fifo2";
		
	mkfifo(myfifo2,0666);
	int fd1=open(myfifo1,O_RDONLY|O_NONBLOCK);
	int fd2=open(myfifo2,O_RDONLY|O_NONBLOCK);
	
	key_t mkey=12590;
	int msgid;
	
	msgid=msgget(mkey,0666|IPC_CREAT);
	FILE *fpin=popen("/home/chidha/cn/cnmar17/q2/d","w");
	while(1)
	{
		fd_set rfd;
		FD_ZERO(&rfd);
		FD_SET(fd1,&rfd);
		FD_SET(fd2,&rfd); 
		
		int maxfd=fd1>fd2?fd1:fd2;
		select(maxfd+1,&rfd,NULL,NULL,NULL);
		
		
		if(FD_ISSET(fd1,&rfd))
		{
			printf("total livesessions are %d\n",chmptr->c);
			char buffer[80]={0};
			int c=read(fd1,buffer,80);
			if(c>0)
			{
			
				printf("%s\n",buffer);
				
				if(buffer[0]=='/'&&buffer[1]=='d')
				{
					fputs(buffer,fpin);
					fflush(fpin);
				}
				else{
				struct msgbuffer snd;
				for(int i=0;i<80;i++)
				snd.msgbuffer[i]=0;
				for(int i=0;i<strlen(buffer);i++)
				{
					snd.msgbuffer[i]=buffer[i];
				}
				snd.msgtype=getpid();
				printf("%s\n",snd.msgbuffer);
				msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),0);
				}
			}
		}
		
		if(FD_ISSET(fd2,&rfd))
		{
			printf("total livesessions are %d\n",chmptr->c);
			char buffer[80]={0};
			int c=read(fd2,buffer,80);
			if(c>0)
			{
				//printf("%s\n",buffer);
				
				if(buffer[0]=='/'&&buffer[1]=='d')
				{
					
					fputs(buffer,fpin);
					fflush(fpin);
				}
				else
				{
				struct msgbuffer snd;
				 
				for(int i=0;i<strlen(buffer);i++)
				{
					snd.msgbuffer[i]=buffer[i];
				}
				
				msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),0);
				}
			}	
		}
			 
	}
		
	

	return 0;	
}
