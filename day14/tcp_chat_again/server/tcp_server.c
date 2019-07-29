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
    int newFd=accept(socketFd,NULL,NULL);
    fd_set rdset;
    int ret;
    fd_set needMoniterFd;
    char buf[1024];
     FD_ZERO(&needMoniterFd);
     FD_SET(STDIN_FILENO,&needMoniterFd);
     FD_SET(socketFd,&needMoniterFd);
    while(1)
    {
        memcpy(&rdset,&needMoniterFd,sizeof(fd_set));
        ret=select(14,&rdset,NULL,NULL,NULL);

        if(ret>0)
        {
            if(FD_ISSET(socketFd,&rdset))
            {
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                FD_SET(newFd,&needMoniterFd);
            }
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret==0)
            {
                printf("bye bye\n");
                break;
            }
            send(newFd,buf,strlen(buf)-1,0);
        }
        if(FD_ISSET(newFd,&rdset))
        {
            bzero(buf,sizeof(buf));
            ret=recv(newFd,buf,sizeof(buf),0);
            if(ret==0)
            {
                printf("cnm\n");
                FD_CLR(newFd,&needMoniterFd);
                close(newFd);
            }
            else{
                  printf("%s\n",buf);
                }     
        }
    }
    }
    return 0;
}
