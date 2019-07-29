#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include<syslog.h>
#include<unistd.h>
#include<sys/select.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<signal.h>
#include<pthread.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/epoll.h>
#include<sys/uio.h>
#define THREAD_ERROR_CHECK(ret,funcName){if(ret!=0){printf("%s:%s\n",funcName,strerror(ret));return -1;}}
#define ARGS_CHECK(argc,val) {if(argc!=val)  {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return -1;}}
#define CHILD_ERROR_CHECK(ret,retVal,funcName) {if(ret==retVal) {perror(funcName);return void(*)-1;}}
#define FILENAME "file"

typedef struct{
    pid_t pid;//子进程的pid
    int pipeFd;//子进程管道对端
    short busy;//用来标记子进程是否忙碌
}process_data_t;

typedef struct
{
    int dataLen;
    char buf[1000];
}train_t;

int makeChild(process_data_t*,int);
int childHandle(int);
int sendFd(int,int);
int recvFd(int,int*);
int tcpInit(int*,char*,char*);
int epollInAdd(int,int);
int tranFile(int);
