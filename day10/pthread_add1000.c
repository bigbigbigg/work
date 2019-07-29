#include <func.h>
#define N 10000000
void *threadFunc(void *p)
{
    int i;
    for(i=0;i<N;i++)
    {
        *(int*)p+=1;
    }
    printf("I am child thread %d\n",*(int*)p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    int val=0;
    ret=pthread_create(&pthid,NULL,threadFunc,&val);
    THREAD_ERROR_CHECK(ret,"pthread_creat");
    int i;
    for(i=0;i<N;i++)
    {
        val=val+1;
    }
    pthread_join(pthid,NULL);//dengdaizixiancheng
    printf("I am main thread\n");
    return 0;
}

