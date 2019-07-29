#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid,ppid;
    pid=getpid();
    ppid=getppid();
    printf("pid=%d ppid=%d uid=%d gid=%d euid=%d egid=%d\n",pid,ppid,getuid(),getgid(),geteuid(),getegid());
    return 0;
}

