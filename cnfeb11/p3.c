#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<semaphore.h>
#include<pthread.h>
#define s3 "/sem3"
#define s "/sem0"
struct msgbuffer{
	long msgtype;
	char msgtext[1024];
};

int msgid;
int pid1=-1;
int pid2=-1,pid3=-1;



void *readf(void *args)
{
	while(1)
	{
		struct msgbuffer snd;
		
		int c=read(0,snd.msgtext,sizeof(snd.msgtext));
		if(c>0)
		{
			int fl;
			printf("enter 2 to send to2 or 1\n");
			scanf("%d",&fl);
			if(fl==2)
			snd.msgtype=pid2;
			else if(fl==1)
			snd.msgtype=pid1;
			
			msgsnd(msgid,&snd,sizeof(snd)-sizeof(long),0);
		}
		
	
	}
}

void *writef(void *args)
{
	while(1)
	{
		struct msgbuffer msg;
		//printf("fl");
		msgrcv(msgid,&msg,sizeof(msg)-sizeof(long),pid3,0);
		
		printf("%s\n",msg.msgtext);
	}
}



int main()
{
	
	key_t key;
	 
	key=ftok("/home/chidha/cnfeb11/prog",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	
	//sem_t *se3=sem_open(s3,O_CREAT,0644,0);
	
	//sleep(5);
	sem_t *se0=sem_open(s,0);
	sem_t *se3=sem_open(s3,0);
	 pid3=getpid();
	struct msgbuffer msg1,msg2;
	msg1.msgtype=pid3;
	msgsnd(msgid,&msg1,sizeof(msg1)-sizeof(long),0);
	msg2.msgtype=pid3;
	msgsnd(msgid,&msg2,sizeof(msg2)-sizeof(long),0);
	
	 
	int tempf=0;
	
	while(tempf<2)
	{
		struct msgbuffer rcv1;
		msgrcv(msgid,&rcv1,sizeof(rcv1)-sizeof(long),0,0);
		int rcvtype=rcv1.msgtype;
		
		if(rcvtype==pid3)
		{
			msgsnd(msgid,&rcv1,sizeof(rcv1)-sizeof(long),0);
		}
		else if(rcvtype==pid2)
		{
		//	rcv.msgtype=pid2;
			msgsnd(msgid,&rcv1,sizeof(rcv1)-sizeof(long),0);
		}
		else if(rcvtype==pid1)
		{
			//rcv.msgtype=pid3;
			msgsnd(msgid,&rcv1,sizeof(rcv1)-sizeof(long),0);
		}
		else
		{
			tempf++;
			if(pid2==-1)
			pid2=rcvtype;
			else if(pid1==-1)
			pid1=rcvtype;
		}
		
	}
	
	
	
	sem_post(se0);
	//sleep(2);
	sem_wait(se3);
	sleep(2);
	printf("%d\n",pid1);
	printf("%d\n",pid2);
	printf("%d\n",pid3);
	
	pthread_t tr,tw;
	
	pthread_create(&tr,NULL,readf,NULL);
	pthread_create(&tw,NULL,writef,NULL);
	
	pthread_join(tr,NULL);
	pthread_join(tw,NULL);
	
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
	
	
}
	
