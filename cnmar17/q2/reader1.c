#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include<sys/msg.h>
#include<sys/socket.h>
 
#include<netinet/in.h>
 
#include<arpa/inet.h>
 #include <sys/shm.h> 

struct livem{
int c;
};

struct memory { 
	 
	int pid1, pid2; 
}; 

struct memory* shmptr; 

struct msgbuffer{
	long msgtype;
	char msgbuffer[80];
};


struct livem *chmptr;

int flag;
void handler(int signum) 
{ 
	// if signum is SIGUSR1, then user 1 is receiving a message from user2 

	if (signum == SIGUSR1) { 
		flag=1;
	} 
} 



void livesession(int port)
{
	int sfd,nsfd;
	
	sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=htons(port);
	connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	
	
	
	while(1)
	{
		char buff[80]={0};
		recv(sfd,buff,80,0);
		if(strlen(buff)>0)
		{printf("received....%s\n",buff);
		if(buff[0]=='e'&&buff[1]=='n'&&buff[2]=='d')
		break;
		}
		
	}
	close(sfd);

}




int main() 
{ 

	int ckey = 12559; 

	// shared memory create 
	int chmid = shmget(ckey, sizeof(struct livem), IPC_CREAT | 0666); 

	// attaching the shared memory 

	chmptr = (struct livem*)shmat(chmid, NULL, 0); 

	flag=1;
	signal(SIGUSR1, handler); 
	
	key_t mkey=12590;
	int msgid;

	msgid=msgget(mkey,0666|IPC_CREAT);
	int skey = 12346; 

	// shared memory create 
	int shmid = shmget(skey, sizeof(struct memory), IPC_CREAT | 0666); 

	// attaching the shared memory 

	shmptr = (struct memory*)shmat(shmid, NULL, 0); 

	
	shmptr->pid1=getpid();
	shmptr->pid2=-1;
	while(shmptr->pid2==-1);
	
	
	printf("%d\n",shmptr->pid1);
	printf("%d\n",shmptr->pid2);
	 
	while(1)
	{
	 
		if(flag==1)
		{
			 
			struct msgbuffer msg;
			msgrcv(msgid,&msg,sizeof(msg)-sizeof(long),0,0);
			printf("received message %s\n",msg.msgbuffer);
			
			int portno=atoi(msg.msgbuffer);
			if(portno>0)
			{
				chmptr->c++;
				livesession(portno);
			}
			
			flag=0;
			kill(shmptr->pid2,SIGUSR1);
		}
	 
	}
	

	return 0;
}
