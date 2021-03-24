#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>

#define port 8080
#define noreq 10

int main()
{
	int sfd,nsfd;
	
	sfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=htons(port);
	connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	
	
	
	while(1)
	{
		printf("enter message.....\n");
		char buff[80]={0};
		read(0,buff,80);
		
		send(sfd,buff,strlen(buff),0);
		
		recv(sfd,buff,80,0);
		
		printf("received....%s\n",buff);
		
	}
	
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
