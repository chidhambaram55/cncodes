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
		 
		recv(5,buff,80,0);
		  
		for(int i=0;i<strlen(buff);i++)
		{
			buff[i]=buff[i]-'A'+'a';
		}
		
		send(5,buff,strlen(buff),0);
		
	}
	
	
	
	
	return 0;
}
