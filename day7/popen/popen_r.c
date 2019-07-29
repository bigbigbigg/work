#include <func.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    fp=popen("./print","r");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128];
    fgets(buf,sizeof(buf),fp);
    printf("buf=%s\n",buf);
    pclose(fp);
    return 0;
}

