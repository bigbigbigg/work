#include <func.h>

int main(int argc,char *argv[])
{
    int fds[2];
    pipe(fds);//读端在fds[0] 写端在fds[1]
    if(!fork())
    {
        close(fds[0]);
        write(fds[1],"Hello",5);
        exit(0);
    }
    else
    {
        close(fds[1]);
        char buf[128]={0};
        read(fds[0],buf,sizeof(buf));
        printf("I am father,gets=%s\n",buf);
        wait(NULL);
    }
    printf("Hello world\n");
    return 0;
}

