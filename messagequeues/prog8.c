#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
//#include<linux/ipc.h>
 
struct msg{
	long msgtype;
	char msgtext[80];
};


int main()
{
	key_t key;
	int msgid;
	key=ftok("/home/chidha/cn/messagequeues/prog7key",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	
	 struct msg buffer;
	 msgrcv(msgid,&buffer,sizeof(buffer)-sizeof(long),2,0);
	 
	 printf("%s\n",buffer.msgtext);
	 
	 struct msqid_ds buff2;
	int c1=msgctl(msgid,IPC_STAT,&buff2);
	if(c1==0)
	{
	
		//struct msg *messg=buff->msg_first;
		printf("%li\n",buff2.msg_qnum);
		//printf("%d\n",buff.
	}
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
	
	
}		
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
	
