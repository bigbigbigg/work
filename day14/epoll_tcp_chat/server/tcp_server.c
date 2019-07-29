#include <func.h>
int tcpInit(int*,char*,char*);
int tcpInit(int *sfd,char *ip,char *port)
{
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    *sfd=socketFd;
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    tcpInit(&socketFd,argv[1],argv[2]);
    int newFd;
    int ret;
    char buf[1024];
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdCount;
    int i;
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,3,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                event.data.fd==newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
            }
        if(evs[i].events==EPOLLIN&&evs[i].data.fd==STDIN_FILENO)
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret==0)
            {
                printf("bye bye\n");
                event.data.fd==newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
                close(newFd);
                break;
            }
            send(newFd,buf,strlen(buf)-1,0);
        }
        if(evs[i].data.fd==newFd)
        {
            bzero(buf,sizeof(buf));
            ret=recv(newFd,buf,sizeof(buf),0);
            if(ret==0)
            {
                printf("cnm\n");
                goto end;
            }
            printf("%s\n",buf);
        }     
        }
    }
end:
    close(newFd);
    close(socketFd);
    return 0;
}

