#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<poll.h>
#include <sys/select.h>

int ports[4]={8000,8001,8002,8003};

int nsfd;
int noreq=50;
char *services[4]={"/home/chidha/cn/sockets/ac1","/home/chidha/cn/sockets/ac2","/home/chidha/cn/sockets/ac3","/home/chidha/cn/sockets/ac2"};

int main()
{
	int sfd[4];
	 
	struct sockaddr_in addr[4];
	
	
	
	 
	for(int i=0;i<4;i++)
	{
		 
		sfd[i]=socket(AF_INET,SOCK_STREAM,0);
		if(sfd[i]<0)
		{
			printf("socket not created");
			exit(0);
		}
		addr[i].sin_family=AF_INET;
		addr[i].sin_addr.s_addr=htonl(INADDR_LOOPBACK);
		addr[i].sin_port=htons(ports[i]);
		if(bind(sfd[i],(struct sockaddr *)&addr[i],sizeof(addr[i]))<0)
		{
			perror("could not bind");
			exit(0);
		}
		listen(sfd[i],noreq);
		printf("%d\n",sfd[i]);
	}
	
	fd_set readset;
	int m=-1;
	for(int i=0;i<4;i++)
	{
		m = (m<sfd[i])?sfd[i]:m;
		
		FD_SET(sfd[i],&readset);
	}
	
	int r;
	pid_t p;
	while(1)
	{
	
		 printf("waiting.....\n");
		 
		 r=select(m+1,&readset,NULL,NULL,NULL);
		 
		 if(r>0)
		 {
		 
		 	for(int i=0;i<4;i++)
		 	{
		 		if(FD_ISSET(sfd[i],&readset))
		 		{
		 			nsfd=accept(sfd[i],NULL,NULL);
		 	 
		 	 		if(nsfd<0)
		 	 		perror("accept failed");
		 	 		else{
				 	dup2(nsfd,5);
				 	//dup2(1,nsfd1);
				 	
				 	int c=fork();
				 	if(c==0)
				 	{
				 		close(sfd[i]);
				 		char *args[1]={NULL};
				 		execv(services[i],args);
				 	}
				 	else
				 	{
				 		close(nsfd);
				 		//dup2(0,temp1);
				 		 
				 	//	write(1,hello,strlen(hello));
				 	}
				 	}
				}
				else
				FD_SET(sfd[i],&readset);
			}	
			 
			 
			 
		 
		 }
		  	 
		 	 
		
	}
	
	
	
	
	return 0;
}
