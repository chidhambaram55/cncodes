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
#include<pthread.h>
#define CONTROLLEN CMSG_LEN(sizeof(int))
#define path "/home/chidha/cn/cnmar17/q1/fd_passing4.socket"

int fdrecv(int usfd)
{
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

return nfd;

}


void convert(char *s)
{	
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		s[i]=s[i]-'a'+'A';
	}
	
}

void* service2(void *nsfd)
{
	int val=*(int*)(nsfd);
	
	while(1)
	{
		 
		char buff[80]={0};
		
		 
		recv(val,buff,80,0);
		 printf("received message for connection oriented service 2 %s\n",buff);
		for(int i=0;i<strlen(buff);i++)
		{
			buff[i]=buff[i]-'a'+'A';
		}
		
		send(val,buff,strlen(buff),0);
		
	}
	
}


void* service3(void *nsfd)
{
	int val=*(int*)(nsfd);
	
	while(1)
	{
		 
		char buff[80]={0};
		
		 
		recv(val,buff,80,0);
		printf("received message for connection oriented service 1 %s\n",buff);
		for(int i=0;i<strlen(buff);i++)
		{
			buff[i]=buff[i]-'A'+'a';
		}
		
		send(val,buff,strlen(buff),0);
		
	}
	
}


void* service1(void *nsfd)
{
	int val=*(int*)(nsfd);
	struct sockaddr_in claddr;
	
	int sz,len=sizeof(claddr);
	
	while(1)
	{
		printf("waiting......\n");
		char buffer[80]={0};
		if(sz=recvfrom(val,buffer,80,0,(struct sockaddr*)&claddr,&len)<0)
		{
			perror("error");
			exit(0);
		}
		
		printf("received a connectionless message....%s\n",buffer);
		
		convert(buffer);
		
		if(sendto(val,buffer,strlen(buffer),0,(struct sockaddr*)&claddr,len)<0)
		{
			perror("error");
			exit(0);
		}
			
			
	}
	
}

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
	
	
	int fds[3];
	fds[0]=fdrecv(usfd);
	pthread_t tid;
	pthread_create(&tid, NULL, service1,(void*)&fds[0]);
	fds[1]=fdrecv(usfd);
	pthread_t tid2;
	pthread_create(&tid2, NULL, service2,(void*)&fds[1]);
	fds[2]=fdrecv(usfd);
	pthread_t tid3;
	pthread_create(&tid3, NULL, service3,(void*)&fds[2]);
	
	 
	
	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	unlink(path);
	


	return 0;
}
