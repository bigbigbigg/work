#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct in_addr netIp;
    int ret;
    ret=inet_aton(argv[1],&netIp);
    if(ret==0)
    {
        fprintf(stderr,"Invalid address\n");
        return -1;
    }
    printf("%x\n",netIp.s_addr);
    return 0;
}

