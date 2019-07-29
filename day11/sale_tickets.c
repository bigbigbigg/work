#include <func.h>
#define N 20
typedef struct 
{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;
void *saleWindows1(void *p)
{
    int i=0;
    Data_t *pArg=(Data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
        printf("I am saleWindows1 start sale %d\n",pArg->tickets);
        pArg->tickets--;
        i++;
        if(!pArg->tickets)
        {
            pthread_cond_signal(&pArg->cond);
        }
        printf("I am saleWindows1 sale finish %d\n",pArg->tickets);
        pthread_mutex_unlock(&pArg->mutex);
        }
        else
        {
        pthread_mutex_unlock(&pArg->mutex);
        printf("I am saleWindows1 ,%d\n",i);
            break;
        }   
   }
    return NULL;
}

void *saleWindows2(void *p)
{
    int i=0;
    Data_t *pArg=(Data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
        printf("I am saleWindows2 start  sale %d\n",pArg->tickets);
        pArg->tickets--;
        i++;
        if(!pArg->tickets)
        {
            pthread_cond_signal(&pArg->cond);
        }
        printf("I am saleWindows2 sale finish %d\n",pArg->tickets);
        pthread_mutex_unlock(&pArg->mutex);
        sleep(1);
        }
        else
        {
        pthread_mutex_unlock(&pArg->mutex);
        printf("I am saleWindows2 %d\n",i);
            break;
        }   
   }
    return NULL;
}

void *setTickets(void *p)
{
    Data_t *pArg=(Data_t*)p;
    pthread_mutex_lock(&pArg->mutex);
    if(pArg->tickets>0)
    {
        pthread_cond_wait(&pArg->cond,&pArg->mutex);
    }
    pArg->tickets=N;
    pthread_mutex_unlock(&pArg->mutex);
}
int main(int argc,char *argv[])
{
    pthread_t pthid,pthid1,pthid2;
    int ret;
    Data_t threadInfo;
    threadInfo.tickets=N;
    ret=pthread_mutex_init(&threadInfo.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    pthread_cond_init(&threadInfo.cond,NULL);
    ret=pthread_create(&pthid2,NULL,setTickets,&threadInfo);
    ret=pthread_create(&pthid,NULL,saleWindows1,&threadInfo);
    ret=pthread_create(&pthid1,NULL,saleWindows2,&threadInfo);
    THREAD_ERROR_CHECK(ret,"pthread_creat");
    long threadRet;
    pthread_join(pthid,(void**)&threadRet);//dengdai
    THREAD_ERROR_CHECK(ret,"pthread_join");
    pthread_join(pthid1,(void**)&threadRet);//dengdai
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("sale over!\n");
    return 0;
}

