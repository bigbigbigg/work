#include "process_pool.h"
//创建子进程，并初始化主数据结构
int makeChild(process_data_t *p,int processNum)
{
    int i;
    pid_t pid;
    int fds[2];
    int ret;
    for(i=0;i<processNum;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(pid==0)
        {
            close(fds[0]);
            childHandle(fds[1]);
        }
        close(fds[1]);
        p[i].pid=pid;
        p[i].pipeFd=fds[0];
        p[i].busy=0;
    }
    return 0;
}
int childHandle(int pipeFd)
{
    int newFd;
    char finishFlag;
    while(1)
    {
        recvFd(pipeFd,&newFd);//接收任务，没有任务子进程会睡觉
        tranFile(newFd);//真正给客户端发文
       // printf("file send sucess\n");//模拟给客户端发文件
        close(newFd);//关闭连
        write(pipeFd,&finishFlag,1);//子进程通知父进程完成任务
    }
}
