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

	int usfd = socket(AF_UNIX,SOCK_STREAM,0);
	
	if(usfd<0)
	{
		perror("not created");
		exit(0);
	}
	
	struct sockaddr_un addr;
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,path);
	 
	
	if(connect(usfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	perror("Could not connect");
	
	
	
	
	
	 int sent_fd;
    struct msghdr message;
    struct iovec iov[1];
    struct cmsghdr *control_message = NULL;
    char ctrl_buf[CMSG_SPACE(sizeof(int))];
    char data[1];
    int res;

    memset(&message, 0, sizeof(struct msghdr));
    memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

    /* For the dummy data */
    iov[0].iov_base = data;
    iov[0].iov_len = sizeof(data);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_control = ctrl_buf;
    message.msg_controllen = CMSG_SPACE(sizeof(int));
    message.msg_iov = iov;
    message.msg_iovlen = 1;
	
int nfd;
    if((res = recvmsg(usfd, &message, 0)) <= 0)
     return res;

    /* Iterate through header to find if there is a file descriptor */
    for(control_message = CMSG_FIRSTHDR(&message);
        control_message != NULL;
        control_message = CMSG_NXTHDR(&message,
                                      control_message))
    {
     if( (control_message->cmsg_level == SOL_SOCKET) &&
         (control_message->cmsg_type == SCM_RIGHTS) )
     {
     nfd= *((int *) CMSG_DATA(control_message));
     }
    }

	
	
	char t[1];
	while(read(nfd,t,1))
	printf("%s",t);
	
	
	
	
	unlink(path);
	


	return 0;
}
