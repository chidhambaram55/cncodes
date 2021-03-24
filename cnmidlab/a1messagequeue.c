#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
struct msgbuffer{
	long msgtype;
	char msgtext[80];
};

int main()
{
	key_t key;
	int msgid;
	key=ftok("/home/chidha/cn/cnmidlab/prog1key",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	 
	while(1)
	{
		struct msgbuffer rec;
		msgrcv(msgid,&rec,sizeof(rec)-sizeof(long),0,0);
		printf("%s\n",rec.msgtext);
	
	}
	
	 
	 
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	
