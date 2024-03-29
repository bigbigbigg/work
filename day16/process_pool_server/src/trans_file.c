#include "process_pool.h"
void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}
int tranFile(int newFd)
{
    int ret;
    signal(SIGPIPE,sigFunc);
    train_t train;
    //发送文件名
    train.dataLen=strlen(FILENAME);
    strcpy(train.buf,FILENAME);
    send(newFd,&train,4+train.dataLen,0);
    //发送文件大小给客户端
    struct stat buf;
    int fd=open(FILENAME,O_RDWR);
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    send(newFd,&train,4+train.dataLen,0);
    //发送文件内容
    
    while((train.dataLen=read(fd,train.buf,sizeof(train.buf))))
    {
        ret=send(newFd,&train,4+train.dataLen,0);
        if(ret==-1)
        {
            return -1;
        }
    }
    send(newFd,&train,4,0);
    return 0;
}

