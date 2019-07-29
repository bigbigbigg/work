#include <func.h>
//循环接受
int recvCycle(int sfd,void *buf,int recvLen)
{
    char *p=(char*)buf;
    int totol=0,ret;
    while(totol<recvLen)
    {
        ret=recv(sfd,p+totol,recvLen-totol,0);
        totol+=ret;
    }
    return 0;
}

