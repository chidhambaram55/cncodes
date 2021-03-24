#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#define port 8080
#define noreq 10

int nsfd;
void serverfunc()
{
	char buffer[80];
	int sz;
	
	while(1)
	{
		sz=recv(nsfd,buffer,80,0);
		buffer[sz]='\0';
		
		printf("Received:%s\n",buffer);
		
		int n=strlen(buffer);
		for(int i=0;i<n;i++)
		{
			buffer[i]=buffer[i]-'a'+'A';
		}
		
		send(nsfd,buffer,n,0);
	}

}

int main()
{
	int sfd,newsckt,valread;
	
	char address[INET_ADDRSTRLEN];
	struct sockaddr_in addr;
	int opt=1;
	int addrlen=sizeof(addr);
	
	char buf[1024]={0};
	
	char *hello="hola from server";
	
	sfd=socket(AF_INET,SOCK_STREAM,0);
	
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=htons(port);
	
	bind(sfd,(struct sockaddr *)&addr,sizeof(addr));
	
	listen(sfd,noreq);
	uint16_t port2;
	while(1)
	{
		printf("waiting......\n");
		nsfd=accept(sfd,NULL,NULL);
		
		int c=fork();
		if(c>0)
		{
			close(nsfd);
			//wait(NULL);
		}
		else
		{
		 	close(sfd);
			serverfunc();
		}
	}
	
	
	
	
	return 0;
}
