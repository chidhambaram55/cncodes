
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
	
	int fd2;
	
	char *myfifo2="/home/chidha/cn/cnmidlab/fifo2";
	
	mkfifo(myfifo2,0666);
	fd1=open(myfifo1,O_RDONLY);
	fd2=open(myfifo2,O_RDONLY);
	while(1)
	{
		
		fd_set rfd;
		FD_ZERO(&rfd);
		FD_SET(fd1,&rfd);
		FD_SET(fd2,&rfd);
		int maxfd=fd1>fd2?fd1:fd2;
		
		select(maxfd+1,&rfd,NULL,NULL,NULL);

		if(FD_ISSET(fd1,&rfd))
		{
			char buff[80]={0};
			read(fd1,buff,80);
			printf("%s\n",buff);
		}
		else if(FD_ISSET(fd2,&rfd))
		{
			char buff[80]={0};
			read(fd2,buff,80);
			printf("%s\n",buff);
		}
	}

	return 0;
}



















