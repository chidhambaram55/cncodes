#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/uio.h>
#include<unistd.h>
int main()
{
	struct iovec iov[3];
	ssize_t nr;
	int fd,i;
	
	char *buf[]={
		"statement one prends...",
		"statement two prends...",
		"statement three prends...."};
		
	fd=open("sample.txt",O_RDWR|O_TRUNC);
	
	for(int i=0;i<3;i++)
	{
		iov[i].iov_base=buf[i];
		iov[i].iov_len=strlen(buf[i])+1;
	}
	
	nr=writev(fd,iov,3);
	printf("characters written %li\n",nr);
	close(fd);
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
