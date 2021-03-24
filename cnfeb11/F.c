#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<semaphore.h>
#define s "/sem0"
#define s1 "/sem1"
#define s2 "/sem2"
#define s3 "/sem3"
int main()
{

	//sem_destroy(se0);
	sem_t *se0=sem_open(s,O_CREAT,0644,0);
	if(se0==SEM_FAILED)
	printf("unsuccessfull");
	sem_t *se3=sem_open(s3,O_CREAT,0644,0);
	sem_t *se1=sem_open(s1,O_CREAT,0644,0);
	sem_t *se2=sem_open(s2,O_CREAT,0644,0);
	//sleep(5);
	//sem_t *se1=sem_open(s1,0);
	//sem_t *se2=sem_open(s2,0);
	//sem_t *se3=sem_open(s3,0);
	sem_wait(se0);
	sem_wait(se0);
	sem_wait(se0);
	sem_post(se1);
	sem_post(se2);
	sem_post(se3);
	
	return 0;
	
}
