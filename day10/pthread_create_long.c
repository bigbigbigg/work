#include <func.h>
void *threadFunc(void *p)
{
    printf("I am child thread%ld\n",(long)p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid1,pthid2;
    int ret;
    long val=1;
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    val=2;
    ret=pthread_create(&pthid2,NULL,threadFunc,(void*)val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_join(pthid1,NULL);//dengdaizixiancheng
    pthread_join(pthid2,NULL);//dengdaizixiancheng
    printf("I am main thread\n");
    return 0;
}

