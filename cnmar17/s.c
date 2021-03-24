#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<poll.h>
#include <sys/select.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include <sys/un.h>
#define path "/home/chidha/cn/cnmar17/q1/fd_passing4.socket"
#define port 8083
int ports[2]={8002,8003};

int nsfd;
int noreq=50;

void fdsend(int nsfd,int fd)
{
 
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

}


int main()
{
	int sfd[3];
	 
	struct sockaddr_in addr[3];
	
	
	
	// uds
	
	int usfd = socket(AF_UNIX,SOCK_STREAM,0);
	
	if(usfd<0)
	{
		perror("not created");
		exit(0);
	}
	
	struct sockaddr_un addr2;
	addr2.sun_family=AF_UNIX;
	strcpy(addr2.sun_path,path);
	if(bind(usfd,(struct sockaddr*)&addr2,sizeof(addr2))<0)
	{
		perror("not binded");
		exit(0);	
	}
	
	
	if(listen(usfd,10)<0)
	{
		perror("could not bind");
		exit(0);
	}
	
	int nsfd2=accept(usfd,NULL,NULL);
	
	if(nsfd2<0)
	{
		perror("not working");
		exit(0);
	}
	 
	//
	
	// connectionless sfd
	addr[2].sin_family=AF_INET;
	addr[2].sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	addr[2].sin_port=port;
	sfd[2]=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd[2]<0)
	{
		perror("socket not created");
		exit(0);
	}
	if(bind(sfd[2],(struct sockaddr*)&addr[2],sizeof(addr[2]))<0)
	{
		perror("unable to bind");
		exit(0);
	}
	
	fdsend(nsfd2,sfd[2]);
	//
	
	// connection oriented sfds
	
	 
	for(int i=0;i<2;i++)
	{
		 
		sfd[i]=socket(AF_INET,SOCK_STREAM,0);
		if(sfd[i]<0)
		{
			printf("socket not created");
			exit(0);
		}
		addr[i].sin_family=AF_INET;
		addr[i].sin_addr.s_addr=htonl(INADDR_LOOPBACK);
		addr[i].sin_port=htons(ports[i]);
		if(bind(sfd[i],(struct sockaddr *)&addr[i],sizeof(addr[i]))<0)
		{
			perror("could not bind");
			exit(0);
		}
		listen(sfd[i],noreq);
		printf("%d\n",sfd[i]);
	}
	
	 //
	
	int c=0;
	
	while(c<2)
	{
	
		fd_set rfd;
		FD_ZERO(&rfd);
		FD_SET(sfd[0],&rfd);
		FD_SET(sfd[1],&rfd); 
		
	 	int maxfd=sfd[0]>sfd[1]?sfd[0]:sfd[1];
		select(maxfd+1,&rfd,NULL,NULL,NULL);
		  
		 	for(int i=0;i<2;i++)
		 	{
		 		if(FD_ISSET(sfd[i],&rfd))
		 		{
		 			int nsfd=accept(sfd[i],NULL,NULL);
		 	 
		 	 		if(nsfd<0)
		 	 		perror("error");
		 	 		else{
				 	 	c++;
				 	 	printf("%d\n",c);
				 	 	fdsend(nsfd2,nsfd);
				 	}
				}
				 
			}	
			 
			 
			 
		 
		 
		 	
	}
	printf("my work completed");
	while(1);
	
	
	
	
	return 0;
}
