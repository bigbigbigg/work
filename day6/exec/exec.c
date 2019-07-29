#include <func.h>

int main(int argc,char *argv[])
{
    execl("./print","niuniu","123","456",NULL);
    printf("Hello world\n");
    return 0;
}

