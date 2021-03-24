#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>

#define port 8003
#define noreq 50

int main()
{
	int sfd;
	
	sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=htons(port);
	if(connect(sfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		perror("could not connect");
		exit(0);
	}
	
	
	while(1)
	{
		printf("enter message.....\n");
		char buff[80]={0};
		read(0,buff,80);
		
		send(sfd,buff,strlen(buff),0);
		
		char buff2[80]={0};
		recv(sfd,buff2,80,0);
		
		printf("received....%s\n",buff2);
		
	}
	
	close(sfd);
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
