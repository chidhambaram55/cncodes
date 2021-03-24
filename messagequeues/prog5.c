#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
struct msgbuffer{
	long msgtype;
	char msgtext[1024];
};

struct mem{
int pid1;
int pid2;
int pid3;
};
 key_t key;
	int msgid;
	
struct mem *mem1;
void *readf(void *args)
{
	while(1)
	{
		struct msgbuffer snd;
		
		int c=read(0,snd.msgtext,sizeof(snd.msgtext));
		if(c>0)
		{
			int fl;
			printf("enter 1 to send to1 or 3\n");
			scanf("%d",&fl);
			if(fl==1)
			snd.msgtype=mem1->pid1;
			else
			snd.msgtype=mem1->pid3;
			
			if(fl==2)
			msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),mem1->pid1);
			else
			msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),mem1->pid3);
		}
		
	
	}
}

void *writef(void *args)
{
	while(1)
	{
		struct msgbuffer msg;
		//printf("fl");
		msgrcv(msgid,&msg,sizeof(msg)-sizeof(long),mem1->pid2,0);
		
		printf("%s\n",msg.msgtext);
	}
}


int main()
{
	//key_t key;
	//int msgid;
	key=ftok("/home/chidha/cn/messagequeues/prog4key",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	
	key_t shkey=ftok("/home/chidha/cn/messagequeues/shr",65);
	
	int shmid=shmget(shkey,1024,0666|IPC_CREAT);
	mem1=(struct mem *)shmat(shmid,(void*)0,0);
	
	mem1->pid2=getpid();
	mem1->pid3=-1;
	//mem1->pid1=-1;
	
	printf("%d\n",mem1->pid2);
	while(mem1->pid3==-1);
	
//	 int flags=fcntl(0,F_GETFL,0);
//	fcntl(0,F_SETFL,flags|O_NONBLOCK);
	 printf("%d\n",mem1->pid1);
	printf("%d\n",mem1->pid3);
	
	
	
	pthread_t tr,tw;
	
	pthread_create(&tr,NULL,readf,NULL);
	pthread_create(&tw,NULL,writef,NULL);
	
	pthread_join(tr,NULL);
	pthread_join(tw,NULL);
	
	/*
	while(1)
	{
		struct msgbuffer snd;
		//send.msgtext={0};
		int c=read(0,snd.msgtext,sizeof(snd.msgtext));
		if(c>0)
		{
			int fl;
			printf("enter 1 to send to1 or 3\n");
			scanf("%d",&fl);
			if(fl==1)
			snd.msgtype=mem1->pid1;
			else
			snd.msgtype=mem1->pid3;
			if(fl==1)
			msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),mem1->pid1);
			else
			msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),mem1->pid3);
		}
		struct msgbuffer msg;
		msgrcv(msgid,&msg,sizeof(msg)-sizeof(long),mem1->pid2,0);
		
		printf("%s\n",msg.msgtext);
		
		
		
		
	}*/
	
	
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
	
}


