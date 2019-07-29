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
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
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
    int ret;
    ret=tcpInit(&socketFd,argv[1],argv[2]);
    if(ret==-1)
    {
        return -1;
    }
    int newFd=accept(socketFd,NULL,NULL);
    printf("newFd=%d\n",newFd);
    char buf[10]={0};
    ret=recv(newFd,buf,5,MSG_DONTWAIT);
    printf("ret=%d %s\n",ret,buf);
    return 0;
}
