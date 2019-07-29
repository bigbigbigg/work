#include <func.h>
long times=0;
void sigFunc(int signum)
{
    time_t now;
    time(&now);
    printf("%s %ld\n", ctime(&now),times);
    times=0;
}
int main(int argc,char *argv[])
{
    signal(SIGPROF,sigFunc);
    struct itimerval t;
    bzero(&t,sizeof(t));
    t.it_value.tv_sec=1;//初始等待时间
    t.it_interval.tv_sec=1;//间隔时间
    int ret;
    sigFunc(0);//kill()
    ret=setitimer(ITIMER_PROF,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
   // char buf[128]={0};
   // read(STDIN_FILENO,buf,sizeof(buf));
   // printf("buf=%s\n",buf);
    double d,f;
    while(1)
    {
        f=12345.23;
        d=6789.123*f;
        times++;
    }
    printf("Hello world\n");
    return 0;
}

