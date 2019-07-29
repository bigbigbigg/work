#include "work_que.h"

void queInit(pQue_t pq,int capacity)
{
    bzero(pq,sizeof(Que_t));
    pq->queCapacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
    return;
}

void queInsert(pQue_t pq,pNode_t pNew)//尾插法
{
    if(pq->queHead==NULL)
    {
        pq->queHead=pNew;
        pq->queTail=pNew;
    }
    else
    {
        pq->queTail->pNext=pNew;
        pq->queTail=pNew;
    }
    pq->queSize++;
}

void queGet(pQue_t pq,pNode_t *pDel)
{
    //头部删除法
    *pDel=pq->queHead;
    pq->queHead=pq->queHead->pNext;
    if(pq->queHead==NULL)
    {
        pq->queTail=NULL;
    }
    pq->queSize--;
}

