#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<string.h>
#define port 8082

void convert(char *s)
{	
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		s[i]=s[i]-'a'+'A';
	}
	
}

int main()
{
	struct sockaddr_in addr;
	
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr.sin_port=port;
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
	
	struct sockaddr_in claddr;
	
	int sz,len=sizeof(claddr);
	
	while(1)
	{
		printf("waiting......\n");
		char buffer[80]={0};
		if(sz=recvfrom(sfd,buffer,80,0,(struct sockaddr*)&claddr,&len)<0)
		{
			perror("error");
			exit(0);
		}
		
		printf("received....%s\n",buffer);
		
		convert(buffer);
		
		if(sendto(sfd,buffer,strlen(buffer),0,(struct sockaddr*)&claddr,len)<0)
		{
			perror("error");
			exit(0);
		}
			
			
	}




	return 0;
}
