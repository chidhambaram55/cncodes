#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
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
	
	struct msgbuffer msg;
	msg.msgtype=getpid();
	//msg.msgtext="NIL";
	msgsnd(msgid,&msg,sizeof(msg)-sizeof(long),0);
	int pid=getpid();
	printf("%d\n",pid);
	struct msgbuffer rec;
	 //int c=0;
	 
		 int c=msgrcv(msgid,&rec,sizeof(rec)-sizeof(long),pid,0);
		 printf("%d\n",c);
	 
		 if(strlen(rec.msgtext)>0)
		 {
	
	
		printf("%s\n",rec.msgtext);
	
		// break;
		}
	  
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
	
}


