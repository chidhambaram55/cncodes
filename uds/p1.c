#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/shm.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<fcntl.h>
#define CONTROLLEN CMSG_LEN(sizeof(int))
#define path "/home/chidha/cn/uds/fd_passing.socket"
int main()
{

	int fd=open("a.txt",O_RDONLY);
	
	int c=0;
	char t[1];
	while(c<5&&read(fd,&t,1))
	{
		if(t[0]=='\n')
		c++;
		
		printf("%s",t);
	}
	
	int usfd = socket(AF_UNIX,SOCK_STREAM,0);
	
	if(usfd<0)
	{
		perror("not created");
		exit(0);
	}
	
	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,path);
	if(bind(usfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		perror("not binded");
		exit(0);	
	}
	
	
	if(listen(usfd,10)<0)
	{
		perror("could not bind");
		exit(0);
	}
	
	int nsfd=accept(usfd,NULL,NULL);
	
	if(nsfd<0)
	{
		perror("not working");
		exit(0);
	}
	 
	 
    struct msghdr message;
    struct iovec iov[1];
    struct cmsghdr *control_message = NULL;
    char ctrl_buf[CMSG_SPACE(sizeof(int))];
    char data[1];

    memset(&message, 0, sizeof(struct msghdr));
    memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

    /* We are passing at least one byte of data so that recvmsg() will not return 0 */
    data[0] = ' ';
    iov[0].iov_base = data;
    iov[0].iov_len = sizeof(data);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_iov = iov;
    message.msg_iovlen = 1;
    message.msg_controllen =  CMSG_SPACE(sizeof(int));
    message.msg_control = ctrl_buf;

    control_message = CMSG_FIRSTHDR(&message);
    control_message->cmsg_level = SOL_SOCKET;
    control_message->cmsg_type = SCM_RIGHTS;
    control_message->cmsg_len = CMSG_LEN(sizeof(int));

    *((int *) CMSG_DATA(control_message)) = fd;
	 
	 
	 
	if(sendmsg(nsfd,&message,0)<0)
	perror("not sent");
	
	unlink(path);
	


	return 0;
}
