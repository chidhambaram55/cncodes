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
		
		fd=open(myfifo,O_WRONLY);
		char buff1[80]={0};
		char buff2[80]={0};
		char buff3[80]={0};
		
		struct iovec iov[3];
		ssize_t nr;
		read(0,buff1,sizeof(buff1));
		iov[0].iov_base=buff1;
		iov[0].iov_len=strlen(buff1);
		read(0,buff2,sizeof(buff2));
		iov[1].iov_base=buff2;
		iov[1].iov_len=strlen(buff2);
		read(0,buff3,sizeof(buff3));
		iov[2].iov_base=buff3;
		iov[2].iov_len=strlen(buff3);
		nr=writev(fd,iov,3); 
		 
		printf("%li\n",nr);
		close(fd);
	}
	
	return 0;
}
