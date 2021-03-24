#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
//#include<linux/ipc.h>
 
struct msgbuf{
	long msgtype;
	char msgtext[80];
};


int main()
{
	key_t key;
	int msgid;
	key=ftok("/home/chidha/cn/messagequeues/prog7key",65);
	
	msgid=msgget(key,0666|IPC_CREAT);
	
	
	struct msgbuf msgi[5]={
				{1,"one"},{2,"two"},{3,"three"},{4,"four"},
				{5,"five"}
				};
	
	for(int i=0;i<5;i++)
	{
		msgsnd(msgid,&msgi[i],sizeof(msgi[i])-sizeof(long),0);
	}
	
	struct msqid_ds buff;
	
	msgctl(msgid,IPC_STAT,&buff);
	
	buff.msg_perm.mode=0400;
	
	msgctl(msgid,IPC_SET,&buff);
	struct msqid_ds buff2;
	msgctl(msgid,IPC_STAT,&buff2);
	printf("%li\n",buff2.msg_qnum);
	struct msg *tmp=buff2.msg_first;
	//printf("%s\n",buff2.msg_first.text);
	msgctl(msgid,IPC_RMID,NULL);
	return 0;
	
	
}		
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
	
