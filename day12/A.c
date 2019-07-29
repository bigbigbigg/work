#include <func.h>
int shmid;
char *p;
void sigFunc(int signum)
{
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
}
int main(int argc,char *argv[])
{
    printf("Hello world\n");
    return 0;
}

