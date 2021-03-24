#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
struct msgbuffer{
	long msgtype;
	char msgtext[1024];
};

int main()
{
	key_t key;
	int msgid;
	key=ftok("/home/chidha/cn/messagequeues/prog1key",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	
	//sleep(5);
	struct msgbuffer msg,msg1,msg2,msg3;
	
	msgrcv(msgid,&msg1,sizeof(msg1)-sizeof(long),0,0);
	
	long pid1=msg1.msgtype;
	
	printf("%li\n",pid1);
	msg.msgtype=pid1;
	 
	read(0,msg.msgtext,sizeof(msg.msgtext));
	 
	msgsnd(msgid,&msg,sizeof(msg)-sizeof(long),0);
	
	 
	 
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
