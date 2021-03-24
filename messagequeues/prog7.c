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
	
	
	struct msg msgi[5]={
				{1,"one"},{2,"two"},{3,"three"},{4,"four"},
				{5,"five"}
				};
	
	for(int i=0;i<5;i++)
	{
		msgsnd(msgid,&msgi[i],sizeof(msgi[i])-sizeof(long),0);
	}
	
	  
	struct msqid_ds buff2;
	int c1=msgctl(msgid,IPC_STAT,&buff2);
	if(c1==0)
	{
	
		//struct msg *messg=buff->msg_first;
		printf("no ofmessages are %li\n",buff2.msg_qnum);
		printf("message lst snd time%li\n",buff2.msg_stime);
		printf("message lst rcv time%li\n",buff2.msg_rtime);
		printf("message queue bytes %li\n",buff2.msg_qbytes);
		printf("last message sender pid %d\n",buff2.msg_lspid);
		printf("last message rcv pid %d\n",buff2.msg_lrpid);
		//printf("%d\n",buff.
	}
	
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
	
	
}		
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
	
