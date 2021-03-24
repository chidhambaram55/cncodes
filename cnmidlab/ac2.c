#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
 
int nsfd;
 	 
int main()
{ 
	while(1)
	{
		 
		char buff[80]={0};
		
		 
		recv(95,buff,80,0);
		 
		char buff2[80]="iam 2. i received";
		
		send(95,buff2,strlen(buff2),0);
		
	}
	
	
	
	
	return 0;
}
