#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/uio.h>
#include<unistd.h>

int main()
{
	
	int fd;
	
	char *myfifo="/home/chidha/cn/cnfeb10/pract";
	
	mkfifo(myfifo,0666);
	
	while(1)
	{
		
		fd=open(myfifo,O_RDONLY);
		char buff1[80]={0};
		char buff2[80]={0};
		char buff3[80]={0};
		 
		 
		struct iovec iov[3];
		ssize_t nr;
		 
		iov[0].iov_base=buff1;
		iov[0].iov_len=10;
		iov[1].iov_base=buff2;
		iov[1].iov_len=10;
		iov[2].iov_base=buff3;
		iov[2].iov_len=10;
	
		nr=readv(fd,iov,3);
		for(int i=0;i<3;i++)
		printf("%s\n",(char*)iov[i].iov_base);
		 
		printf("%li\n",nr);
		close(fd);
	}
	
	return 0;
}
