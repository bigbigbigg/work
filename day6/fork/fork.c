#include <func.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        printf("I am child mypid=%d,myppid=%d\n",getpid(),getppid());
        while(1);
    }
    else
    {
        printf("I am parent mypid=%d,mychildpid=%d\n",getpid(),pid);
        while(1);
    }
    return 0;
}

