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

int ports=8081;
 
int noreq=50;
char *services="/home/chidha/cn/cnmidlab/ac3";

int main()
{
	int sfd;
	 
	struct sockaddr_in addr;
	
	
	 
		sfd=socket(AF_INET,SOCK_STREAM,0);
		if(sfd<0)
		{
			printf("socket not created");
			exit(0);
		}
		addr.sin_family=AF_INET;
		addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
		addr.sin_port=htons(ports);
		if(bind(sfd,(struct sockaddr *)&addr,sizeof(addr))<0)
		{
			perror("could not bind");
			exit(0);
		}
		listen(sfd,noreq);
		printf("%d\n",sfd);
	
	
	
	 
	pid_t p;
	while(1)
	{
	
		 	int nsfd=accept(sfd,NULL,NULL);
		 	 
		 	 if(nsfd<0)
		 	{
		 	 	perror("accept failed");
		 	 	printf("$$$$$");
		 	 }
		 	 else
		 	 {
				dup2(nsfd,5);
				 	//dup2(1,nsfd1);
				 	
				int c=fork();
			 	if(c==0)
			 	{
			 		close(sfd);
			 		char *args[1]={NULL};
			 		execv(services,args);
			 	}
			 	else
			 	{
			 		close(nsfd);
			 		 
			 	}
			 }
		 
	 	
	}
	
	
	
	
	return 0;
}
