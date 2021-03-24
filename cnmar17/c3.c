#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<string.h>
#define port 8083
#define clport 8081
 

int main()
{
	struct sockaddr_in addr;
	
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=clport;
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		perror("socket not created");
		exit(0);
	}
	if(bind(sfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		perror("unable to bind");
		exit(0);
	}
	
	struct sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	seraddr.sin_port=port;
	int sz,len=sizeof(seraddr);
	
	while(1)
	{
		printf("enter a string......\n");
		char buffer[80]={0};
		
		read(0,buffer,80);
		
		
		if(sendto(sfd,buffer,strlen(buffer),0,(struct sockaddr*)&seraddr,len)<0)
		{
			printf("$$$$$");
			perror("error");
			exit(0);
		}
		
		printf("sent...\n");
		if(sz=recvfrom(sfd,buffer,80,0,(struct sockaddr*)&seraddr,&len)<0)
		{
			perror("error");
			exit(0);
		}
		
		printf("received....%s\n",buffer);
		
		
		
		
			
			
	}




	return 0;
}
