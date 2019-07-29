#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd,fd1;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
    dup2(1,100);
    fd1=dup2(fd,1);
    close(fd);
    printf("fd1=%d\n",fd1);
    printf("you cant see\n");
    dup2(100,1);
    printf("you can see\n");
    return 0;
}
