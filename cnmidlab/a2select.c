
#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
//#include<pcap.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include <sys/stat.h> 
#include <sys/types.h> 


int main()
{
	int fd1;
	
	char *myfifo1="/home/chidha/cn/cnmidlab/fifo1";
	
	mkfifo(myfifo1,0666);
	
	 
	fd1=open(myfifo1,O_WRONLY);
	 
	while(1)
	{
		
		char buff[80]={0};
		read(0,buff,80);
		write(fd1,buff,strlen(buff));
		 
	}

	return 0;
}



















